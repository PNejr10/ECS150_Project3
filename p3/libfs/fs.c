#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "disk.h"
#include "fs.h"

/* TODO: Phase 1 */

int mount = 0;
struct  __attribute__((__packed__)) superBlock {
	char	 	signature[8];
	uint16_t 	total_Block_counter;
	uint16_t 	Root_Dir;
	uint16_t 	Data_Block;
	uint16_t 	Amout_Data_Block;
	uint8_t 	Fat_block;
	uint8_t		padding [4079];
};

struct  __attribute__((__packed__)) fatBlock {
	uint16_t 	*Fat_Block_index;
	
};

struct  __attribute__((__packed__)) rootDir {
	char* 		Filename;
	uint32_t 	file_Size;
	uint16_t 	index;
	uint8_t 	padding[10];
};

struct superBlock *sb;
struct fatBlock Fb; 
struct rootDir *rd[FS_FILE_MAX_COUNT];

int fs_mount(const char *diskname)
{
	sb = malloc(sizeof(struct superBlock));
	//Fb = malloc(sizeof(struct fatBlock));
 	rd[FS_FILE_MAX_COUNT] = malloc (128 * sizeof(struct rootDir));


	int open = block_disk_open(diskname);
	if(open == -1){
		return -1;
	}
	if(block_read(0, &sb) == -1){
		return -1;
	}
	if(strcomp(sb->signature,"ECS150FS", 8) != 0){
		return -1;
	}
	if(sb->total_Block_counter != block_disk_count()){
		return -1;
	}

	Fb.Fat_Block_index = malloc(BLOCK_SIZE *(sb->Fat_block)* 2);
	for(int i = 1; i <= sb->Fat_block; i ++){
		block_read(i, &Fb.Fat_Block_index[i-1]);	
	}

	block_read(sb->Fat_block+1,&rd);
	mount = 1;
	return 0;


}

int fs_umount(void)
{
	if (mount == 0)	
		return -1;
	if(block_read(0, &sb) == -1){
		return -1;
	}
	for(int i = 1; i <= sb->Fat_block; i++){
		block_write(i, &Fb.Fat_Block_index[i-1]);	
	}
	block_write(sb->Fat_block+1,&rd);
	int close = block_disk_close();
	if(close == -1){
		return -1;
	}
	else{
		mount =0;
		return 0;
	} 
	

}

int fs_info(void)
{
	/* TODO: Phase 1 */

	printf("FS info: \n");
	printf("Virtual Desk %i\n", sb->total_Block_counter);
	printf("Root Dir %i\n", sb->Root_Dir);
	printf("Data Block %i\n", sb->Data_Block);
	printf("Amout of Data Block %i\n", sb->Amout_Data_Block);
	printf("Number of Fat %i\n", sb->Fat_block);
	printf("Padding %i\n", sb->padding);
	int zeros=0;
	for (int  i =0; i< sb->Fat_block; i++ ){
		if(Fb.Fat_Block_index[i] == 0)
			zeros++;
	}
	printf("Fat ratio %i\n", zeros/sb->Fat_block);

}

int fs_create(const char *filename) // tester.c
{
	/* TODO: Phase 2 
	 @filename is invalid, get the size of the array
	*/
	if(strlen(filename) > FS_FILENAME_LEN || mount == 0)
		return -1;
	int add = 0;
	for(int i =0; i < FS_FILE_MAX_COUNT; i++){
		if(strcmp(rd[i]->Filename, filename) == 0)
			return -1;
		
		if(strcmp(rd[i]->Filename, "/0")==0){
			strcpy(rd[i]->Filename, filename);
			rd[i]->file_Size = 0;
			rd[i]->index = 0xFFFF;
			add = 1;
			break;
		}
	}
	if (add == 1)
		return 0;
	else 
		return -1;
}

int fs_delete(const char *filename)
{
	/* TODO: Phase 2 */
	if(strlen(filename) > FS_FILENAME_LEN || mount == 0)
		return -1;
	
	int delete = 0;
	int fat_index = 0;
	for(int i =0; i < FS_FILE_MAX_COUNT; i++){

		if(strcmp(filename, rd[i]->Filename)==0){
			rd[i]->Filename = "\0";
			rd[i]->file_Size = 0;
			fat_index =rd[i]->index;
			rd[i]->index = 0xFFFF;
			break;
		}
	}

	if (delete == 1){
		for(int i =fat_index+1; i<FS_FILE_MAX_COUNT; i++){
			Fb.Fat_Block_index[i] = 0;
			if(Fb.Fat_Block_index[i+1] == 0xFFFF)
				break; 
		}
		return 0;
	}
	
	else 
		return -1;
	
}

int fs_ls(void)
{
	/* TODO: Phase 2 */
	if(mount == 0)
		return -1;
	printf("FS ls \n");
	for(int i =0; i< FS_FILE_MAX_COUNT; i++){
		if(strcmp(rd[i]->Filename, "\0")!=0){
			printf("File name %s, File size %d, First Data Block %d\n", 
			rd[i]->Filename, rd[i]->file_Size, rd[i]->index);
		}

	}
	return 0;

}

int fs_open(const char *filename)
{
	/* TODO: Phase 3 */
}

int fs_close(int fd)
{
	/* TODO: Phase 3 */
}

int fs_stat(int fd)
{
	/* TODO: Phase 3 */
}

int fs_lseek(int fd, size_t offset)
{
	/* TODO: Phase 3 */
}

int fs_write(int fd, void *buf, size_t count)
{
	/* TODO: Phase 4 */
}

int fs_read(int fd, void *buf, size_t count)
{
	/* TODO: Phase 4 */
}

