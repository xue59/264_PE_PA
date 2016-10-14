#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bmp.h"

/* check whether a header is valid
 * assume that header has been read from fptr
 * the position of the indicator of fptr is not certain
 * could be at the beginning of the file, end of the file or 
 * anywhere in the file
 * note that the check is only for this exercise/assignment
 * in general, the format is more complicated
 */

int Is_BMP_Header_Valid(BMP_Header* header, FILE *fptr) {
  // Make sure this is a BMP file
  if (header->type != 0x4d42) {
     return FALSE;
  }
  // skip the two unused reserved fields

  // check the offset from beginning of file to image data
  // essentially the size of the BMP header
  // BMP_HEADER_SIZE for this exercise/assignment
  if (header->offset != BMP_HEADER_SIZE) {
     return FALSE;
  }
      
  // check the DIB header size == DIB_HEADER_SIZE
  // For this exercise/assignment
  if (header->DIB_header_size != DIB_HEADER_SIZE) {
     return FALSE;
  }

  // Make sure there is only one image plane
  if (header->planes != 1) {
    return FALSE;
  }
  // Make sure there is no compression
  if (header->compression != 0) {
    return FALSE;
  }

  // skip the test for xresolution, yresolution

  // ncolours and importantcolours should be 0
  if (header->ncolours != 0) {
    return FALSE;
  }
  if (header->importantcolours != 0) {
    return FALSE;
  }
  
  // Make sure we are getting 24 bits per pixel
  // or 16 bits per pixel
  // only for this assignment
  if (header->bits != 24 && header->bits != 16) {
    return FALSE;
  }

  // fill in extra to check for file size, image size
  // based on bits, width, and height
  
  // for image size 
  if (header->bits == 24){
    int numPix = header->width;
    int rowData = numPix*3;
    if (rowData%4 != 0){
      rowData = (4-((numPix*3)%4) + numPix*3); 
    }
    
    if(header->imagesize != rowData * header->height){
      return FALSE;
    }
  }else if(header->bits == 16){
    int numPix = header->width;
    int rowData = numPix*2;

    if (rowData%4 != 0){
      rowData = (4-((numPix*3)%4) + numPix*3); 
    }
    
    if(header->imagesize != rowData * header->height){
      return FALSE;
    }
  }
  
  //for file size
  fseek(fptr, 0, SEEK_SET);
  int sz;
  fseek(fptr, 0, SEEK_END);
  sz = ftell(fptr);
  if(header->size != sz){
    return FALSE;
  }

  return TRUE;
}

/* The input argument is the source file pointer. 
 * The function returns an address to a dynamically allocated BMP_Image only 
 * if the file * contains a valid image file 
 * Otherwise, return NULL
 * If the function cannot get the necessary memory to store the image, also 
 * return NULL
 * Any error messages should be printed to stderr
 */
BMP_Image *Read_BMP_Image(FILE* fptr) {

  // go to the beginning of the file
  fseek(fptr,0, SEEK_SET);
  BMP_Image *bmp_image = NULL;

  //Allocate memory for BMP_Image*;
  bmp_image = malloc(sizeof(BMP_Image));
  if(bmp_image == NULL){
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
  }

  //Read the first 54 bytes of the source into the header
  fread(&bmp_image->header, 1, 54, fptr);

  // if read successful, check validity of header
  if((Is_BMP_Header_Valid(&bmp_image->header, fptr)) != 1){
    fprintf(stderr, "Can't open file for output\n");
    return FALSE;   
  }
  
  // Allocate memory for image data
  bmp_image -> data = malloc(bmp_image->header.imagesize);
  if(bmp_image -> data == NULL){
    return NULL;
  }
  
  // read in the image data
  fseek(fptr, 54,SEEK_SET);
  fread(bmp_image->data, 1, bmp_image->header.imagesize, fptr);

  return bmp_image;
}

/* The input arguments are the destination file pointer, BMP_Image *image.
 * The function write the header and image data into the destination file.
 * return TRUE if write is successful
 * FALSE otherwise
 */
int Write_BMP_Image(FILE* fptr, BMP_Image* image) 
{
  // go to the beginning of the file
  fseek(fptr, 0, SEEK_SET);
  
  // write header
  fwrite(&image->header, sizeof(unsigned char), 54, fptr);
  
  // write image data
  fseek(fptr, 0, SEEK_END);
  fwrite(image->data, sizeof(unsigned char), image->header.imagesize, fptr);
  
  Free_BMP_Image(image);
  return TRUE;
}

/* The input argument is the BMP_Image pointer. The function frees memory of 
 * the BMP_Image.
 */
void Free_BMP_Image(BMP_Image* image) {
  free(image->data);
  free(image);
}

// convert 24 to 16 bits 
// need modification.......................
BMP_Image *Convert_24_to_16_BMP_Image(BMP_Image *image){
  // create a new image reflected from the given image
  BMP_Image *t_image = NULL;
  int height = image->header.height;
  int width = image->header.width;

  //Allocate memory for BMP_Image*;
   t_image = malloc(sizeof(BMP_Image));
   if(t_image == NULL){
     fprintf(stderr, "Error allocating memory\n");
     return NULL;
   }
  
  // assign header to new header and make 3 changes 
  t_image->header = image->header;
  t_image->header.bits = 16;
  int newPadding;
  if (((width*2)%4) == 0){
    newPadding = 0;
  }else{
    newPadding = 4 - ((width*2) % 4);  
  }
  
  t_image->header.imagesize = width * height * 2 + newPadding*height; 
  t_image->header.size = t_image->header.imagesize + 54;

  // Allocate memory for image data
  t_image -> data = malloc(t_image->header.imagesize);
  if(t_image -> data == NULL){
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
  }
  
  unsigned char t_char1;
  unsigned char t_char2;
  unsigned char o_charB;
  unsigned char o_charG;
  unsigned char o_charR;
  int bytesRow_24 = image->header.imagesize / image->header.height;
  int bytesRow_16 = t_image->header.imagesize / t_image->header.height;
  int bytesPix_24 = image->header.bits / 8;
  int bytesPix_16 = t_image->header.bits / 8;
  
  int count_new;
  int count_old;
  int j;
  int i;
  int count;
  int x_y;
  int xp1_y;
  int xm1_ym1;
  int x_ym1;
  int xp1_ym1;
  
  unsigned char oldpixel;
  unsigned char newpixel;
  int quant_error=0;;
  unsigned int mask1=0x1f;
  // add padding on
  
    for(i = 0; i <t_image->header.imagesize; i++){
     
	t_image->data[i] = 0x00;
      
    
  }
  // creat another array to store the temp 24bit image DATA
  unsigned int *temp_data = malloc(image->header.imagesize * (sizeof(int)));
  int *error_data = malloc(image->header.imagesize * (sizeof(int)));
  for(i =0; i<image->header.imagesize; i++){
    error_data[i]=0;
  }
  if(image -> data == NULL){
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
  }
  //=====================24 - 24===========================================
  for(i =0; i<image->header.imagesize; i++){
    temp_data[i]=(unsigned int)image->data[i];
  }
  //=====================================================
  for(i = (image->header.height-1); i >= 0; i--){
    for (j = 0; j < image->header.width*3; j++){
      count = i*bytesRow_24 + j;
      
      //=========B-G-R
      x_y = count;	
      xp1_y = count + 3;
      xm1_ym1 = count - 3 - bytesRow_24;
      x_ym1 = count - bytesRow_24;
      xp1_ym1 = count + 3 - bytesRow_24;
	
      // printf("%d,%d, ", (int)error_data[x_y],(int)error_data[x_y]/16);

      temp_data[x_y] = (int)temp_data[x_y] + (int)error_data[x_y]/16;
	
      if (temp_data[x_y] < 0){
	temp_data[x_y] = 0;
      }else if (quant_error > 255){
	temp_data[x_y] = 255;
      }
	
      oldpixel  = temp_data[x_y];
	
      newpixel  = (oldpixel >> 3)&mask1;
      //printf("old=%x,new=%x,",oldpixel,newpixel*255/31);

      quant_error  = (int)oldpixel - (int)newpixel * 255 / 31; 
      
      //printf("diff=%d\n", quant_error);
	
      if(j+3>=0&&j+3 <(image->header.width*3)){
	error_data[xp1_y] = error_data[xp1_y]   + quant_error * 7;
      }
      if(j-3>=0&&j-3 <image->header.width*3&&i-1>=0&&i-1 <image->header.height){
	error_data[xm1_ym1] = error_data[xm1_ym1] + quant_error * 3;
      }
      if(i-1>=0&&i-1 <image->header.height){
	error_data[x_ym1] = error_data[x_ym1]   + quant_error * 5;
      }
      if(j+3>=0&&j+3 <image->header.width*3&&i-1>=0&&i-1 <image->header.height){
	error_data[xp1_ym1] = error_data[xp1_ym1] +quant_error * 1;    
      }
    }
  }
  
  //=================================================================
  
  //change DATA from 24 to 16
  for(i = (height-1); i >= 0; i--){
    for (j = 0; j < width; j++){
      count_new = i*bytesRow_16 + j* bytesPix_16;
      count_old = i*bytesRow_24 + j* bytesPix_24;
      
      o_charB = temp_data[count_old];
      o_charG = temp_data[count_old + 1];
      o_charR = temp_data[count_old + 2];
      
      t_char1 = (o_charB>>3) | (((o_charG<<2)>>5)<<5);
      t_char2 = ((o_charR>>3)<<2) | (o_charG>>6);
      
      t_image->data[count_new] = t_char1;
      t_image->data[count_new + 1] = t_char2;
    }
  }
  //printf("%d=\n",t_image->header.imagesize/t_image->header.height);
  Free_BMP_Image(image);
  free(temp_data);
  return t_image;
}






















//====================16 to 24=======================================================
BMP_Image *Convert_16_to_24_BMP_Image(BMP_Image *image){
  // create a new image reflected from the given image
  BMP_Image *t_image = NULL;
  int height = image->header.height;
  int width = image->header.width;

  //Allocate memory for BMP_Image*;
   t_image = malloc(sizeof(BMP_Image));
   if(t_image == NULL){
     fprintf(stderr, "Error allocating memory\n");
     return NULL;
   }
  
  // assign header to new 24 bits  header
  t_image->header = image->header;
  t_image->header.bits = 24;
  int newPadding;
  if (((width*3)%4) == 0){
    newPadding = 0;
  }else{
    newPadding = 4 - ((width*3) % 4);  
  }
  
  t_image->header.imagesize = width * height * 3 + newPadding*height; 
  t_image->header.size = t_image->header.imagesize + 54;

  // Allocate memory for image data
  t_image -> data = malloc(t_image->header.imagesize);
  if(t_image -> data == NULL){
    fprintf(stderr, "Error allocating memory\n");
    return NULL;
  }
  
  unsigned char t_charB;
  unsigned char t_charG;
  unsigned char t_charR;  
  unsigned char o_char1;
  unsigned char o_char2;
  //short red;
  //short blu;
  //short gre;
  int bytesRow_16 = image->header.imagesize / image->header.height;
  int bytesRow_24 = t_image->header.imagesize / t_image->header.height;
  int bytesPix_16 = image->header.bits / 8;
  int bytesPix_24 = t_image->header.bits / 8;
  int count;
  int count_new;
  int count_old;
  int j;
  int i;

  // dont change =====================================

  if (newPadding != 0){
    for(i = 0; i < height; i++){
      for(j = 0; j < (width*3 + newPadding); j++){
	count = i*bytesRow_24 + j;
	t_image->data[count] = (unsigned char)0;
      }
    }
  }
  
  //change DATA from 16 to 24
  // dont change ==========================================
  for(i = 0; i < height; i++){
    for (j = 0; j < width; j++){
      count_new = i*bytesRow_24 + j* bytesPix_24;
      count_old = i*bytesRow_16 + j* bytesPix_16;
      
      o_char1 = image->data[count_old];
      o_char2 = image->data[count_old + 1];
      
      t_charB = (o_char1 & 0b00011111);
      t_charG = ((o_char1 & 0b11100000) >> 5) | ((o_char2 & 0b00000011) << 3);
      t_charR = (o_char2 & 0b01111100) >> 2;
      
      t_charB = (t_charB * 255) / 31;
      t_charG = (t_charG * 255) / 31;
      t_charR = (t_charR * 255) / 31;
      
      t_image->data[count_new] = t_charB;
      t_image->data[count_new + 1] = t_charG;
      t_image->data[count_new + 2] = t_charR;
    }
  }
  // dont change =============================================================
  Free_BMP_Image(image);
  return t_image;
}
