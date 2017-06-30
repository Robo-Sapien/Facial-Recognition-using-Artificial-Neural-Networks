#include <stdio.h>
#include "pgmimage.h"
#include "backprop.h"
extern void exit();
#define TARGET_HIGH 0.9
#define TARGET_LOW 0.1

//USING ONLY ONE OUTPUT UNIT
/*** This is the target output encoding for a network with one output unit.
     It scans the image name, and if it's an image of me (js) then
     it sets the target unit to HIGH; otherwise it sets it to LOW.
     Remember, units are indexed starting at 1, so target unit 1
     is the one to change....  ***/

void load_target(IMAGE *img,BPNN *net)
{
  int scale;
  char userid[40], head[40], expression[40], eyes[40], photo[40];

  userid[0] = head[0] = expression[0] = eyes[0] = photo[0] = '\0';

  /*** scan in the image features ***/
  sscanf(NAME(img), "%[^_]_%[^_]_%[^_]_%[^_]_%d.%[^_]",
    userid, head, expression, eyes, &scale, photo);//check the image name for the details
int i;
    for (i=0;i<4;i++)net->target[i+1]=TARGET_LOW;
    for (i=0; i<4; i++) net->target[i+1];
    if (!strcmp(head, "straight")) {
        net->target[1] = TARGET_HIGH; //
    }
    else if (!strcmp(head, "left")) {
        net->target[2] = TARGET_HIGH; //
    }
    else if (!strcmp(head, "right")) {
        net->target[3] = TARGET_HIGH; //
    }
    else if (!strcmp(head, "up")) {
        net->target[4] = TARGET_HIGH; //
    }
}
void load_input_with_image(IMAGE *img,BPNN *net)
{
  double *units;
  int nr, nc, imgsize, i, j, k;

  nr = ROWS(img);
  nc = COLS(img);
  imgsize = nr * nc;;
  if (imgsize != net->input_n) {
    printf("LOAD_INPUT_WITH_IMAGE: This image has %d pixels,\n", imgsize);
    printf("   but your net has %d input units.  I give up.\n", net->input_n);
    exit (-1);
  }

  units = net->input_units;
  k = 1;
  for (i = 0; i < nr; i++) {
    for (j = 0; j < nc; j++) {
      units[k] = ((double) img_getpixel(img, i, j)) / 255.0;
      k++;
    }
  }
}
