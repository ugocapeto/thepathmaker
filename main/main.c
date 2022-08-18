#include "header.h"

int main(
 int argc,
 char* argv[]
)

{

 FILE *fp;
 char filename[MAXLINE];
 char filename_source_image[MAXLINE];
 char filename_tracing_path_points[MAXLINE];
 char filename_tracing_path_segments[MAXLINE];
 char filename_output_image[MAXLINE];
 arrayHeader *tracing_path;
 int err_flag;
 int *source_image_arr;
 int width;
 int height;
 int *output_image_arr;
 int dot_radius;
 int dot_radius2;

 /*
 Let's read in the input file
 */

 fp= fopen("thepathmaker_input.txt","r");
 if ( fp == NULL ) {
    fprintf(stdout,"thepathmaker_input.txt not found!\n");
    return 1;
 }

 /*
 Get filename for source image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"source image = %s\n",filename);

 strcpy(filename_source_image,filename);

 /*
 Get filename for tracing path points
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"tracing path points = %s\n",filename);

 strcpy(filename_tracing_path_points,filename);

 /*
 Get filename for tracing path segments
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"tracing path segments = %s\n",filename);

 strcpy(filename_tracing_path_segments,filename);

 /*
 Get filename for output image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"output image = %s\n",filename);

 strcpy(filename_output_image,filename);

 /*
 Get dot radius
 */

 fscanf(fp,"%d",&dot_radius);

 fprintf(stdout,"dot radius = %d\n",dot_radius);

 /*
 Get dot radius 2
 */

 fscanf(fp,"%d",&dot_radius2);

 fprintf(stdout,"dot radius 2 (antialiasing) = %d\n",dot_radius2);

 /*
 Done reading the input file
 */

 fclose(fp);

 /*
 Load source image
 */

 err_flag= load_image(
  filename_source_image,
  &source_image_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"source image file %s not loaded!\n",filename_source_image);
    return 1;
 }

 /*
 Create tracing path container
 */

 point_container_new(
  &tracing_path
 );

 /*
 Load tracing path
 */

 tracing_path_load(
  filename_tracing_path_points,
  filename_tracing_path_segments,
  tracing_path
 );

 /*
 Allocate memory for the output image
 */

 myCalloc(output_image_arr,int,width*height,sizeof(int));

 /*
 Write tracing path to output image
 */

 tracing_path_write_to_image(
  width,
  height,
  output_image_arr,
  tracing_path
 );

 if ( !(dot_radius2 >= dot_radius) ) {
    fprintf(stdout,"dot radius 2 must be greater or equal to dot radius!\n");
    return 1;
 }

 antialias_image(
  width,
  height,
  output_image_arr,
  dot_radius,
  dot_radius2
 );

 /*
 Write output image
 */

 err_flag= write_image(
  filename_output_image,
  output_image_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"output image file %s not written!\n",filename_output_image);
    return 1;
 }

 return 0;

}
