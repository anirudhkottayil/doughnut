#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

void print_tor(unsigned char torus[], int rows, int cols){
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
}

int main(){
  int rows = 16;
  int cols = 36;
  int R = 4;
  int r = R / 3;
  int half = R + r;
  int span = 2*half;
  const char* ramp = " .:-=+*#%@";
  int len = strlen(ramp);

  double tilt = 36;
  double A = 0; double B = 0;

  unsigned char torus[cols*rows];
  int depth[cols*rows];
  
  double x,y,ny,z,nz,xa,xb,za,yb,ar,br,tr,phir,thr;
  int x1,y1,nz1;
  for (int i = 0; i < 1400; i++){
    memset(torus, 0, cols * rows);
    memset(depth, 0, cols * rows * sizeof(int));

    ar =  A * M_PI / 180.0;
    br =  B * M_PI / 180.0;
    tr =  tilt * M_PI / 180.0;

    for (int phi = 0; phi < 360; phi++){
      phir = phi * M_PI / 180.0;
      for (int theta = 0; theta < 360; theta++){ 
        thr = theta * M_PI / 180.0;
        x = (R + r*cos(thr)) * cos(phir);
        y = (R + r*cos(thr)) * sin(phir);
        z = r*sin(thr);

        xa = x*cos(ar) - z*sin(ar);
        za = x*sin(ar) + z*cos(ar);

        xb = xa*cos(br) - y*sin(br);
        yb = xa*sin(br) + y*cos(br);

        ny = yb * cos(tr) - za * sin(tr);
        nz = yb * sin(tr) + za * cos(tr);


        x1  = (int)(((xb + half) / (double)span) * (cols - 1) + 0.5);
        y1  = (int)(((ny + half) / (double)span) * (rows - 1) + 0.5);
        nz1 = (int)(((nz + half) / (double)span) * (len  - 1) + 0.5);

        if (x1 < 0 || x1 >= cols || y1 < 0 || y1 >= rows) continue;
        if (nz1 < 0) nz1 = 0;
        if (nz1 >= len) nz1 = len - 1;


        if (depth[y1*cols + x1] <= nz1){
          depth[y1*cols + x1] = nz1;
          torus[y1*cols + x1] = ramp[nz1];
        }
      }
    }
    print_tor(torus, rows, cols); // Fix the array formatting to use a single printf("%s", torus) instead of a print function
    printf("\033[%dA\r", rows);
    fflush(stdout);
    A += 1.2;
    B += 0.7;
    if (A >= 360) A-=360;
    if (B >= 360) B-=360;
    usleep(150);
  }

  return 0;
}
