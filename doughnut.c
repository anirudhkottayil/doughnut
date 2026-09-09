#include <stdio.h>
#include <stdlib.h>
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

  int rows = 40;
  int cols = 84;
  int R = 12;
  int r = R / 4;

  unsigned char* torus = calloc( cols * rows, 1);
  
  double x,y;
  int x1, y1;
  for (int phi = 0; phi < 361; phi++){
    for (int theta = 0; theta < 181; theta++){
      x = (R + r*cosf(theta * M_PI /180)) * cosf(phi * M_PI /180);
      y = (R + r*cosf(theta * M_PI /180)) * sinf(phi * M_PI/180);
      x1 = (int)(((x + 15) / 30) * (cols - 1) + 0.5f);
      y1 = (int)(((y + 15) / 30) * (rows - 1) + 0.5f);
      torus[y1*cols + x1] = '.';
    }
  }

  for (int i = 0; i < rows; i++){
    int offset = i * cols;
    for (int j = 0; j < cols; j++){
      if (torus[offset + j] != '.') {
        printf("%c", ' ');
      } else {
        printf("%c", torus[offset + j]);
      }
    }
    printf("\n");
  }

  free(torus);




  return 0;
}
