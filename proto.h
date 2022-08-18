void antialias_image(
 int width,
 int height,
 int *image_arr,
 int radius,
 int radius2
);

int point_add(
 arrayHeader *point_container,
 double x,
 double y
);

void point_container_free(
 arrayHeader *point_container
);

void point_container_new(
 arrayHeader **ppoint_container
);

void point_get(
 arrayHeader *point_container,
 int point,
 double *px,
 double *py
);

void point_set(
 arrayHeader *point_container,
 int point,
 double x,
 double y
);

void tracing_path_load(
 char *filename_tracing_path_points,
 char *filename_tracing_path_segments,
 arrayHeader *tracing_path
);

void tracing_path_write_to_image(
 int width,
 int height,
 int *image_arr,
 arrayHeader *tracing_path
);
