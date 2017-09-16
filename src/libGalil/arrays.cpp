/*! \file arrays.c
*
* Function calls for uploading and downloading arrays with CSV files.
*
*/

#include "gclibo.h"
#define _CRT_SECURE_NO_WARNINGS //use traditional C calls like strncpy()
#include <stdlib.h> //atoi, atof
#include <string.h> //strcpy
#include <stdio.h> //fopen
#include <math.h> //log()


//! Structure to create a linked list for array data.
struct H_ArrayData
{
	char name[16]; //copy of array name
	char* data; //pointer to the ASCII array data
	int len; //length of data
	int elements; //found data elements for properly dimensioning on download
	int index; //access index into data for write/read operations

	struct H_ArrayData* next; //pointer to next ArrayNode in the list

	//The following fields are only valid on the head node
	struct H_ArrayData * tail; //if this node is the head node, last ptr will be maintained for faster tail insertion
	int count; //if this node is the head node, count will be maintained for total number of arrays
	//note, head node also holds array data
};
typedef struct H_ArrayData ArrayNode;

//! Function to initialize the memory of a new node
void H_InitArrayNode(ArrayNode* node)
{
	node->count = 0;
	node->data = 0;
	node->index = 0;
	node->len = 0;
	node->name[0] = 0;
	node->next = 0; //null indicates end of list
	node->tail = 0;
	node->elements = 0;
	//could memset to zero...
}

//! Add an ArrayData node to the linked list.
GReturn H_AddArray(ArrayNode* head, char* name, char* data)
{
	ArrayNode* node; //the node to fill with data
	if (head->count == 0) //no need to malloc, just fill the head
		node = head;
	else
	{
		node = (ArrayNode*) malloc(sizeof(ArrayNode));
		if (node) //malloc ok
			H_InitArrayNode(node);
		else
			return G_BAD_FULL_MEMORY; //malloc failed
	}

	node->data = data; //copy pointer
	strcpy(node->name, name); //copy name array
	node->len = strlen(node->data); //output of GArrayUpload is null terminated.

	head->count++; //count the node we just made
	head->tail->next = node; //link the new node. If node == head this breaks the last-node-next-null guarantee
	node->next = 0; //enforce the last-node-next-null guarantee
	head->tail = node; //update head's tail pointer
	
	return G_NO_ERROR;
}

//! Frees all memory downsteam of node. After passing list head to this function, all memory is freed and the head node is invalid.
void H_FreeArrays(ArrayNode* node)
{
	if (node == 0) return; //recursive exit condition
	free(node->data); //free this node's data
	H_FreeArrays(node->next); //let downstream nodes recursvely free their data
	free(node->next); //free the struct this node points to
	//no need to free node, the head is declared on the stack
}

//! Uplaods a particular array and adds it to the linked list.
GReturn H_UploadArrayToList(GCon g, ArrayNode* head, char* name)
{
	GReturn rc = G_NO_ERROR; //return code
	char* array_buf; //buffer to hold array as it's uploaded
	if (!(array_buf = (char*) malloc(MAXARRAY))) //allocate memory for single array upload
		return G_BAD_FULL_MEMORY;

	if ((rc = GArrayUpload(g, name, G_BOUNDS, G_BOUNDS, G_CR, array_buf, MAXARRAY)) != G_NO_ERROR) //get this array's data
		return rc;

	return H_AddArray(head, name, array_buf); //push the data into the array linked list
}

//! Creates a buffer on the heap to write data, and adds it to the linked list.
GReturn H_CreateArrayNode(ArrayNode* head, char* name)
{
	char* array_buf; //buffer to hold array data
	if (!(array_buf = (char*) malloc(MAXARRAY))) //allocate memory for single array upload
		return G_BAD_FULL_MEMORY;
	array_buf[0] = 0; //null terminate so len is correct when added
	return H_AddArray(head, name, array_buf); //push the data into the array linked list
}

//! Adds an array element to an array node.
GReturn H_ArrayAddElement(ArrayNode* node, GCStringIn element)
{
	int len = strlen(element);
	if ((len + node->index + 1) >= MAXARRAY) //+1 for \r
		return G_BAD_FULL_MEMORY;

	strcpy(node->data + node->index, element); //copy the data to the array
	node->index += len;
	node->data[node->index++] = '\r'; //delim
	node->data[node->index] = 0; //null terminate
	node->len = node->index; //maintain len field	
	node->elements++; //count the element just added
	return G_NO_ERROR;
}

//!Walks through the array linked list, downloading each.
/*!
*  \warning This function will call DA and DM which modifies the controllers' array table.
*  This should NOT be done while running record array (see RA/RC/RD) or while using the
*  MODBUS array sharing feature (see ME). To prevent any possibility of array table issues,
*  dimension all the arrays used in the applications with the appropriate lengths before use
*  and comment out the *array table modification* section below.
*/
GReturn H_DownloadArraysFromList(GCon g, ArrayNode* head)
{
	ArrayNode* node = head;
	GReturn rc = G_NO_ERROR;
	char command[32]; //buffer for holding command calls
	while ((node != 0) && (rc == G_NO_ERROR))
	{

		//*** Start array table modification
		//    Deallocate the array in case it's the wrong size.
		sprintf(command, "DA %s[]", node->name);
		if ((rc = GCmd(g, command)) != G_NO_ERROR)
			return rc;

		//    Dimension the array with the correct length.
		sprintf(command, "DM %s[%i]", node->name, node->elements);
		if ((rc = GCmd(g, command)) != G_NO_ERROR)
			return rc;
		//*** End array table modification

		rc = GArrayDownload(g, node->name, G_BOUNDS, G_BOUNDS, node->data); //download the array
		node = node->next;
	}
	return rc;
}

//! After filling the array list, this function is called to write out the CSV.
GReturn H_WriteArrayCsv(ArrayNode* head, GCStringIn file_path)
{
	if (head->count == 0) //nothing to do
		return G_NO_ERROR;

	FILE *file; //file pointer
	size_t bytes; //length of data to write
	size_t bytes_written; //bytes actually written to file
	int colcount = 0; //column counter, used to prevent a trailing colon
	int data_left = head->count; //counter for number of arrays that still have data left to be written
	ArrayNode* node = head; //pointer to an array node in the list

	if (!(file = fopen(file_path, "wb"))) //open file for writing, binary mode
		return G_BAD_FILE;

	//write the header
	do
	{
		bytes = strlen(node->name);
		bytes_written = fwrite(node->name, 1, bytes, file);
		colcount++;

		if (colcount != head->count) //write a comma if it's not the last column
		{
			bytes_written += fwrite(",", 1, 1, file);
			bytes++;
		}
		else //write a carriage return
		{
			bytes_written += fwrite("\r", 1, 1, file);
			bytes++;
		}

		if (bytes_written != bytes) //ensure we wrote what we wanted
		{
			fclose(file);
			return G_BAD_FILE;
		}
		node = node->next;
	} while (node != 0);


	//now write the data
	while (data_left) //continue writing rows as long as arrays have data to write
	{
		node = head;
		colcount = 0;
		do //write one row
		{
			bytes_written = 0;
			bytes = 0;
			if (node->index != node->len) //data available
			{
				while ((node->data[node->index] != '\r') //search for the carriage return delim
					&& (node->index < node->len)) //unless we reach the end
				{
					if (node->data[node->index] != ' ') //don't keep spaces
					{
						bytes_written += fwrite(node->data + node->index, 1, 1, file);
						bytes++;
					}
					node->index++;
				}

				if (node->index == node->len) //reached the end of this data
					data_left--; //decrement counter to indicate one less array with data to write

				node->index++; //jump over \r delim
			}

			colcount++; //count the cell we just filled
			if (colcount != head->count) //write a comma if it's not the last column
			{
				bytes_written += fwrite(",", 1, 1, file);
				bytes++;
			}
			else //write a carriage return, even on the last line
			{
				bytes_written += fwrite("\r", 1, 1, file);
				bytes++;
			}

			//check for write failure
			if (bytes_written != bytes)
			{
				fclose(file);
				return G_BAD_FILE;
			}

			node = node->next;
		} while (node != 0);
	} //while (data_left)

	fclose(file);
	return G_NO_ERROR;
}


GReturn GCALL GArrayDownloadFile(GCon g, GCStringIn file_path)
{
	FILE *file;
	GReturn rc = G_NO_ERROR;
	char name[32]; //buffer for holding name of array
	int n; //index into name
	char element[32]; //buffer for holding ascii array element value
	int e; //index into element
	char c; //char currently being read

	//Linked list to hold array data as it's organized for download
	ArrayNode head; //first element (list head) lives on this stack
	ArrayNode* node; //current node
	H_InitArrayNode(&head);
	head.tail = &head; //circular reference

	if (!(file = fopen(file_path, "rb"))) //open file for reading, binary mode
		return G_BAD_FILE;

	//read out header, making a new ArrayNode for each 
	n = 0;
	c = 0;
	while (fread(&c, 1, 1, file))
	{
		if ((c == ',') || (c == '\r'))
		{
			if (n)
			{
				name[n] = 0; //null terminate
				n = 0; // next time start filling name from start
				H_CreateArrayNode(&head, name);
			}

			if (c == '\r') //end of line
				break; //done reading headers
		}
		else
		{
			name[n++] = c;
		}
	}

	//read each line of the file, pushing each cell into its corresponding ArrayNode
	node = &head;
	e = 0;
	while (fread(&c, 1, 1, file))
	{
		if ((c == ',') || (c == '\r'))
		{
			if (e) //if anything read into element
			{
				element[e] = 0; //null terminate
				H_ArrayAddElement(node, element);
				e = 0; //start writing at start of element on next pass
			}
			node = node->next; //go to the next array
			if (node == 0) node = &head; //wrap around to front
		}
		else
		{
			element[e++] = c;
		}
	}



	fclose(file); //done with file

	//By here, all the array data is in the linked-list starting at head, just download it
	rc = H_DownloadArraysFromList(g, &head);
	H_FreeArrays(&head); // don't forget to free memory
	return rc;
}


GReturn GCALL GArrayUploadFile(GCon g, GCStringIn file_path, GCStringIn names)
{

	GReturn rc = G_NO_ERROR; //return code
	long bytes; //strlen placeholder
	char array_names[1024]; //buffer to hold copy of names, or response to list arrays LA
	char name[32]; //buffer to hold a single array name
	int i, n; //indices
	char c; //holder for the char currently being read
	int bracket = 0; //increments when [ seen on a line, [ marks the end of the array name

	//Linked list to hold array data
	ArrayNode head; //first element (list head) lives on this stack
	H_InitArrayNode(&head);
	head.tail = &head; //circular reference

	if (names == 0) //check for null pointer in arg
		bytes = 0;
	else
		bytes = strlen(strcpy(array_names, names));

	if (bytes == 0) //null or "", need to get the arrays from the controller
	{
		if ((rc = GCmdT(g, "LA", array_names, sizeof(array_names), 0)) != G_NO_ERROR) //Trimming command, get names from List Arrays (LA)
			return rc; //no mallocs yet, so we can exit without free

		bytes = strlen(array_names); //count the response
	}

	n = 0; //n is name[] index
	for (i = 0; i < bytes; i++)
	{
		c = array_names[i];

		if (c == '[')
			bracket++; //[ marks the end of the array name
		
		if ((c != ' ') && (c != '\r') && (c != '\n') && !bracket)
		{
			name[n++] = array_names[i]; //keep the char
		}
		
		
		if ((c == ' ') || (c == '\r') || (i == bytes - 1))
		{
			if (n) //if we have anything in name
			{
				name[n] = 0; // null terminate name
				n = 0; // next time start filling name from start
				bracket = 0; //forget any brackets we've seen

				if ((rc = H_UploadArrayToList(g, &head, name)) != G_NO_ERROR) //Add data to list
				{
					H_FreeArrays(&head); // don't forget to free memory
					return rc;
				}
			}
			continue;
		}

	}

	//By here, all the array data is in the linked-list starting at head.
	rc = H_WriteArrayCsv(&head, file_path);
	H_FreeArrays(&head); // don't forget to free memory
	return rc;
}
