#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/ioctl.h>
#include <errno.h>
#include <math.h>


int main(){
  // struct winsize w;
  // if(ioctl(0, TIOCGWINSZ, &w) == -1){
  //   perror("ioctl");
  //   return 1;
  // }
  // int rows = w.ws_row;
  // int cols = w.ws_col;

  int rows = 28;
  int cols = 54;
  int R = 8;
  int r = R / 4;
  const char* ramp = " .:-=+*#%@";
  int len = strlen(ramp);

  unsigned char* torus = calloc( cols * rows, 1);
  int* depth = calloc(cols * rows, sizeof(int));
  
  double x,y,ny,z,nz;
  double tilt = 36;
  int x1, y1, nz1;
  for (int phi = 0; phi < 361; phi++){
    for (int theta = 0; theta < 361; theta++){ // theta += 6 gives similar result for current dimensions of 40 and 80
      x = (R + r*cosf(theta * M_PI /180)) * cosf(phi * M_PI /180);
      y = (R + r*cosf(theta * M_PI /180)) * sinf(phi * M_PI/180);
      z = r*sinf(theta * M_PI /180);
      ny = (y * cosf(tilt * M_PI /180)) - (z * sinf(tilt * M_PI/180));
      nz = (y * sinf(tilt * M_PI /180)) + (z * cosf(tilt * M_PI /180));
      nz1 = (int)(((nz + 10)/ 20) * (len - 1) + 0.5f);
      x1 = (int)(((x + 12) / 24) * (cols - 1) + 0.5f);
      y1 = (int)(((ny + 12) / 24) * (rows - 1) + 0.5f);
      if (depth[y1*cols + x1] <= nz1){
        depth[y1*cols + x1] = nz1;
        torus[y1*cols + x1] = ramp[nz1];
      }
    }
  }

  for (int i = 0; i < rows; i++){
    int offset = i * cols;
    for (int j = 0; j < cols; j++){
      if (torus[offset + j] == 0) {
        printf(" ");
      } else {
        printf("%c", torus[offset + j]);
      }
    }
    printf("\n");
  }

  free(torus);
  free(depth);




  return 0;
}
