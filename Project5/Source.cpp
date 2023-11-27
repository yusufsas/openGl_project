#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
//#define _CRT_SECURE_NO_WARNINGS 





#define GRID_SIZE 32
#define SMALL_GRID_SIZE 2
#define BORDER_WIDTH_BIG 3
#define BORDER_WIDTH_SMALL 1



void drawObject(float cordinate[][2], int size) {
    glLineWidth(5);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_LINE_STRIP);

    glColor4f(1.0f, 0.0f, 0.0f, 0.4f);

    for (int i = 0; i < size; i++) {
        glVertex2f(cordinate[i][0], cordinate[i][1]);
    }

    glEnd();
    glDisable(GL_BLEND);
}


void drawSquare(float x, float y, float size, float r, float g, float b, float alpha, int borderWidth) {
    // Çizim iþlemi
    glColor4f(r, g, b, alpha); 
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y - size);
    glVertex2f(x, y - size);
    glEnd();

    // Border çizimi
    glLineWidth(borderWidth);
    glColor4f(0.0f, 0.0f, 0.0f, alpha);  
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y - size);
    glVertex2f(x, y - size);
    glEnd();
}


int isPointInsideShape(float x, float y, float coordinates[][2], int vertexCount) {
    int i, j;
    int isInside = 0;
    for (i = 0, j = vertexCount - 1; i < vertexCount; j = i++) {
        if (((coordinates[i][1] > y) != (coordinates[j][1] > y)) &&
            (x < (coordinates[j][0] - coordinates[i][0]) * (y - coordinates[i][1]) / (coordinates[j][1] - coordinates[i][1]) + coordinates[i][0])) {
            isInside = !isInside;
        }
    }
    return isInside;
}
int drawGrid(int sect) {

    FILE* ile;
    fopen_s(&ile, "output.txt", "r"); 

    if (ile == NULL) {
        fprintf(stderr, "Dosya açýlamadý.\n");
        return 0;
    }

    char line[800] = { 0 };
    
    float kordinatlar[100][2] = { 0 };
    int selection = sect;
    int index = 0;
    while (fgets(line, sizeof(line), ile) != NULL) {
        if (line[0] == '1' && line[1] == 'B' && selection == 1) {
            
            char* start = strchr(line, '(');
            while (start != NULL) {
                int x, y;
                if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                    kordinatlar[index][0] = x / 64.0;
                    kordinatlar[index][1] = 1.0f-(y / 64.0);
                    index++;
                    start = strchr(start + 1, '(');
                }
                else {
                    start = NULL;
                }
            }
        }
        else if (line[0] == '2' && line[1] == 'B' && selection == 2) {
            
            char* start = strchr(line, '(');
            while (start != NULL) {
                int x, y;
                if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                    kordinatlar[index][0] = x / 64.0;
                    kordinatlar[index][1] = 1.0f -( y / 64.0);
                    index++;
                    start = strchr(start + 1, '(');
                }
                else {
                    start = NULL;
                }
            }
        }
        else if (line[0] == '3' && line[1] == 'B' && selection == 3) {
           
            char* start = strchr(line, '(');
            while (start != NULL) {
                int x, y;
                if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                    kordinatlar[index][0] = x / 64.0;
                    kordinatlar[index][1] = 1.0f - (y / 64.0);
                    index++;
                    start = strchr(start + 1, '(');
                }
                else {
                    start = NULL;
                }
            }
        }
        else if (line[0] == '4' && selection == 4) {
            
            char* start = strchr(line, '(');
            while (start != NULL) {
                int x, y;
                if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                    kordinatlar[index][0] = x / 64.0;
                    kordinatlar[index][1] = 1.0f - (y / 64.0);
                    index++;
                    start = strchr(start + 1, '(');
                }
                else {
                    start = NULL;
                }
            }
        }
    }

    fclose(ile);




    float kordinatlar1[10][2] = { 0 };
    float kordinatlar2[10][2] = { 0 };
    float kordinatlar3[10][2] = { 0 };
    int i = 0, j = 0;
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int flag = 0; // Kontrol bayraðý

    for (i = 0; i < 10; i++) {
        if (kordinatlar[i][0] == 0 && kordinatlar[i][1] == 0) {
            break; 
        }

        if (flag == 0) {
            kordinatlar1[counter1][0] = kordinatlar[i][0];
            kordinatlar1[counter1][1] = kordinatlar[i][1];
            counter1++;

            for (int k = 0; k < counter1 - 1; k++) {
                if (kordinatlar[i][0] == kordinatlar[k][0] && kordinatlar[i][1] == kordinatlar[k][1]) {
                    flag = 1;

                }
            }
        }
        else if (flag==1) {
            kordinatlar2[counter2][0] = kordinatlar[i][0];
            kordinatlar2[counter2][1] = kordinatlar[i][1];
            counter2++;

            for (int k = 0; k < counter2 - 1; k++) {
                if (kordinatlar[i][0] == kordinatlar[k][0] && kordinatlar[i][1] == kordinatlar[k][1]) {
                    flag = 2;

                }
            }
        }
        else if(flag==2) {
            kordinatlar3[counter3][0] = kordinatlar[i][0];
            kordinatlar3[counter3][1] = kordinatlar[i][1];
            counter3++;
        }
        else {
            continue;
        }
    }

    int alan1 = 0;
    int alan2 = 0;


   
    float squareSize = 1.0f / GRID_SIZE;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            float x = i * squareSize;
            float y = j * squareSize; // Yüksekliði tersine çevirdik.

        


            float smallSquareSize = squareSize / SMALL_GRID_SIZE;
            for (int k = 0; k < SMALL_GRID_SIZE; k++) {
                for (int l = 0; l < SMALL_GRID_SIZE; l++) {
                    float smallX = x + k * smallSquareSize;
                    float smallY = y + l * smallSquareSize; // Yüksekliði tersine çevirdik.
                    float smallX2 = x + (k + 1) * smallSquareSize;
                    float smallY2 = y + (l + 1) * smallSquareSize;

                    float smallSquareCenterX = smallX;
                    float smallSquareCenterY = smallY - smallSquareSize;

               
                    int isPointInside = isPointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar2, counter2);
                  
                    if (isPointInside) {
                        alan1 += 1;
                        drawSquare(smallX, smallY, smallSquareSize, 0.0f, 0.0f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
                    }
                    else {
                        drawSquare(smallX, smallY, smallSquareSize, 0.0f, 0.0f, 0.5f, 1.0f, BORDER_WIDTH_SMALL); // Þeklin dýþýndaki kareleri ayný renkle boyama
                    }
                }
            }
            for (int k = 0; k < SMALL_GRID_SIZE; k++) {
                for (int l = 0; l < SMALL_GRID_SIZE; l++) {
                    float smallX = x + k * smallSquareSize;
                    float smallY = y + l * smallSquareSize;        // Yüksekliði tersine çevirdik.
                    float smallX2 = x + (k + 1) * smallSquareSize;
                    float smallY2 = y + (l + 1) * smallSquareSize;

                    float smallSquareCenterX = smallX ;
                    float smallSquareCenterY = smallY -smallSquareSize ;

           
                    int isPointInside = isPointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar1, counter1);
                    
                    if (isPointInside) {
                        alan1 += 1;
                        drawSquare(smallX, smallY, smallSquareSize, 0.0f, 0.0f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
                    }
                   
                }
            }
            for (int k = 0; k < SMALL_GRID_SIZE; k++) {
                for (int l = 0; l < SMALL_GRID_SIZE; l++) {
                    float smallX = x + k * smallSquareSize;
                    float smallY = y + l * smallSquareSize;        // Yüksekliði tersine çevirdik.
                    float smallX2 = x + (k + 1) * smallSquareSize;
                    float smallY2 = y + (l + 1) * smallSquareSize;

                    float smallSquareCenterX = smallX;
                    float smallSquareCenterY = smallY - smallSquareSize;

                    /* int insideShape1 = pointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar1, 4);*/
                    int isPointInside = isPointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar3, counter1);
                    //
                    //// Küçük karenin rengini belirleme
                    if (isPointInside) {
                        alan1 += 1;
                        drawSquare(smallX, smallY, smallSquareSize, 0.0f, 0.0f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
                    }
                 
                }
            }



        }
    }
    
    drawObject(kordinatlar3, counter3);
    drawObject(kordinatlar2, counter2);
    drawObject(kordinatlar1, counter1);
    
    int alan = alan1 + alan2;
    return alan;
    
    
         
   }
   int drawGrid2(int sect) {

       FILE* ile;
       fopen_s(&ile, "output.txt", "r"); // Dosyayý okuma modunda aç

       if (ile == NULL) {
           fprintf(stderr, "Dosya açýlamadý.\n");
           return 0;
       }

       char line[800] = { 0 };

       float kordinatlar[100][2] = { 0 };
       int selection = sect;
       int index = 0;
       while (fgets(line, sizeof(line), ile) != NULL) {
           if (line[0] == '1' && line[1] == 'B' && selection == 1) {
               // Seçilen satýrýn içindeki koordinatlarý bul
               char* start = strchr(line, '(');
               while (start != NULL) {
                   int x, y;
                   if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                       kordinatlar[index][0] = x / 64.0;
                       kordinatlar[index][1] = 1.0f - (y / 64.0);
                       index++;
                       start = strchr(start + 1, '(');
                   }
                   else {
                       start = NULL;
                   }
               }
           }
           else if (line[0] == '2' && line[1] == 'B' && selection == 2) {
               // Seçilen satýrýn içindeki koordinatlarý bul
               char* start = strchr(line, '(');
               while (start != NULL) {
                   int x, y;
                   if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                       kordinatlar[index][0] = x / 64.0;
                       kordinatlar[index][1] = 1.0f - (y / 64.0);
                       index++;
                       start = strchr(start + 1, '(');
                   }
                   else {
                       start = NULL;
                   }
               }
           }
           else if (line[0] == '3' && line[1] == 'B' && selection == 3) {
               // Seçilen satýrýn içindeki koordinatlarý bul
               char* start = strchr(line, '(');
               while (start != NULL) {
                   int x, y;
                   if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                       kordinatlar[index][0] = x / 64.0;
                       kordinatlar[index][1] = 1.0f - (y / 64.0);
                       index++;
                       start = strchr(start + 1, '(');
                   }
                   else {
                       start = NULL;
                   }
               }
           }
           else if (line[0] == '4' && line[1] == 'B' && selection == 4) {
               // Seçilen satýrýn içindeki koordinatlarý bul
               char* start = strchr(line, '(');
               while (start != NULL) {
                   int x, y;
                   if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                       kordinatlar[index][0] = x / 64.0;
                       kordinatlar[index][1] = 1.0f - (y / 64.0);
                       index++;
                       start = strchr(start + 1, '(');
                   }
                   else {
                       start = NULL;
                   }
               }
           }
       }

       fclose(ile);




       float kordinatlar1[10][2] = { 0 };
       float kordinatlar2[10][2] = { 0 };
       float kordinatlar3[10][2] = { 0 };
       int i = 0, j = 0;
       int counter1 = 0;
       int counter2 = 0;
       int counter3 = 0;
       int flag = 0; // Kontrol bayraðý

       for (i = 0; i < 10; i++) {
           if (kordinatlar[i][0] == 0 && kordinatlar[i][1] == 0) {
               break; // 0,0'a gelindiðinde döngüyü durdur
           }

           if (flag == 0) {
               kordinatlar1[counter1][0] = kordinatlar[i][0];
               kordinatlar1[counter1][1] = kordinatlar[i][1];
               counter1++;

               for (int k = 0; k < counter1 - 1; k++) {
                   if (kordinatlar[i][0] == kordinatlar[k][0] && kordinatlar[i][1] == kordinatlar[k][1]) {
                       flag = 1;

                   }
               }
           }
           else if (flag == 1) {
               kordinatlar2[counter2][0] = kordinatlar[i][0];
               kordinatlar2[counter2][1] = kordinatlar[i][1];
               counter2++;

               for (int k = 0; k < counter2 - 1; k++) {
                   if (kordinatlar[i][0] == kordinatlar[k][0] && kordinatlar[i][1] == kordinatlar[k][1]) {
                       flag = 2;

                   }
               }
           }
           else {
               kordinatlar3[counter3][0] = kordinatlar[i][0];
               kordinatlar3[counter3][1] = kordinatlar[i][1];
               counter3++;
           }
       }

       int alan1 = 0;
       int alan2 = 0;
       int alan4 = 0;
       int alan8 = 0;



       float squareSize = 1.0f / GRID_SIZE;

       for (int i = 0; i < GRID_SIZE; i++) {
           for (int j = 0; j < GRID_SIZE; j++) {
               float x = i * squareSize;
               float y = j * squareSize; // Yüksekliði tersine çevirdik.

               
 



               float smallSquareSize = squareSize / SMALL_GRID_SIZE;
               for (int k = 0; k < SMALL_GRID_SIZE; k++) {
                   for (int l = 0; l < SMALL_GRID_SIZE; l++) {
                       float smallX = x + k * smallSquareSize;
                       float smallY = y + l * smallSquareSize; // Yüksekliði tersine çevirdik.
                       float smallX2 = x + (k + 1) * smallSquareSize;
                       float smallY2 = y + (l + 1) * smallSquareSize;

                       float smallSquareCenterX = smallX;
                       float smallSquareCenterY = smallY - smallSquareSize;


                       int isPointInside = isPointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar2, counter2);

                       if (isPointInside) {
                           alan1 += 1;
                           drawSquare(smallX, smallY, smallSquareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama // Þeklin içindeki kareleri farklý renkle boyama
                       }
                       else {
                           drawSquare(smallX, smallY, smallSquareSize, 0.0f, 0.0f, 0.5f, 1.0f, BORDER_WIDTH_SMALL); // Þeklin dýþýndaki kareleri ayný renkle boyama
                       }
                   }
               }
               for (int k = 0; k < SMALL_GRID_SIZE; k++) {
                   for (int l = 0; l < SMALL_GRID_SIZE; l++) {
                       float smallX = x + k * smallSquareSize;
                       float smallY = y + l * smallSquareSize;        // Yüksekliði tersine çevirdik.
                       float smallX2 = x + (k + 1) * smallSquareSize;
                       float smallY2 = y + (l + 1) * smallSquareSize;

                       float smallSquareCenterX = smallX;
                       float smallSquareCenterY = smallY - smallSquareSize;


                       int isPointInside = isPointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar1, counter1);

                       if (isPointInside) {
                           alan1 += 1;
                           drawSquare(smallX, smallY, smallSquareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama // Þeklin içindeki kareleri farklý renkle boyama
                       }

                   }
               }
               for (int k = 0; k < SMALL_GRID_SIZE; k++) {
                   for (int l = 0; l < SMALL_GRID_SIZE; l++) {
                       float smallX = x + k * smallSquareSize;
                       float smallY = y + l * smallSquareSize;        // Yüksekliði tersine çevirdik.
                       float smallX2 = x + (k + 1) * smallSquareSize;
                       float smallY2 = y + (l + 1) * smallSquareSize;

                       float smallSquareCenterX = smallX;
                       float smallSquareCenterY = smallY - smallSquareSize;

                       /* int insideShape1 = pointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar1, 4);*/
                       int isPointInside = isPointInsideShape(smallSquareCenterX, smallSquareCenterY, kordinatlar3, counter1);
                       //
                       //// Küçük karenin rengini belirleme
                       if (isPointInside) {
                           alan1 += 1;
                           drawSquare(smallX, smallY, smallSquareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama // Þeklin içindeki kareleri farklý renkle boyama
                       }

                   }
               }



           }
       }

       for (int i = 0; i < GRID_SIZE; i++) {
           for (int j = 0; j < GRID_SIZE; j++) {
               float x = i * squareSize;
               float y = j * squareSize; // Yüksekliði tersine çevirdik.
           

               float SquareCenterX = x;
               float SquareCenterY = y - 0.5 * squareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar1, counter1);
               if (isPointInside) {
                   alan2 += 1;
                   drawSquare(x, y, squareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }
           
           
           
           
           }}
       for (int i = 0; i < GRID_SIZE; i++) {
           for (int j = 0; j < GRID_SIZE; j++) {
               float x = i * squareSize;
               float y = j * squareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x;
               float SquareCenterY = y - 0.5 * squareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar2, counter2);
               if (isPointInside) {
                   alan2 += 1;
                   drawSquare(x, y, squareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }
       for (int i = 0; i < GRID_SIZE; i++) {
           for (int j = 0; j < GRID_SIZE; j++) {
               float x = i * squareSize;
               float y = j * squareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x;
               float SquareCenterY = y - 0.5 * squareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar3, counter3);
               if (isPointInside) {
                   alan2 += 1;
                   drawSquare(x, y, squareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }
       float dsquareSize = 1.0f / (GRID_SIZE/2);
       for (int i = 0; i < GRID_SIZE/2; i++) {
           for (int j = 0; j < GRID_SIZE/2; j++) {
               float x = i * dsquareSize;
               float y = j * dsquareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x + 0.5*dsquareSize;
               float SquareCenterY = y - 0.5* dsquareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar1, counter1);
               if (isPointInside) {
                   alan4 += 1;
                   drawSquare(x, y, dsquareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }
       for (int i = 0; i < GRID_SIZE / 2; i++) {
           for (int j = 0; j < GRID_SIZE / 2; j++) {
               float x = i * dsquareSize;
               float y = j * dsquareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x + 0.5 * dsquareSize;
               float SquareCenterY = y - 0.5 * dsquareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar2, counter2);
               if (isPointInside) {
                   alan4 += 1;
                   drawSquare(x, y, dsquareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }
       for (int i = 0; i < GRID_SIZE / 2; i++) {
           for (int j = 0; j < GRID_SIZE / 2; j++) {
               float x = i * dsquareSize;
               float y = j * dsquareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x + 0.5 * dsquareSize;
               float SquareCenterY = y - 0.5 * dsquareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar3, counter3);
               if (isPointInside) {
                   alan4 += 1;
                   drawSquare(x, y, dsquareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }

       float d2squareSize = 1.0f / (GRID_SIZE / 4);
       for (int i = 0; i < GRID_SIZE / 4; i++) {
           for (int j = 0; j < GRID_SIZE / 4; j++) {
               float x = i * d2squareSize;
               float y = j * d2squareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x + 0.4 * d2squareSize;
               float SquareCenterY = y - 0.4 * d2squareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar1, counter1);
               if (isPointInside) {
                   alan8 += 1;
                   drawSquare(x, y, d2squareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }
       for (int i = 0; i < GRID_SIZE / 4; i++) {
           for (int j = 0; j < GRID_SIZE / 4; j++) {
               float x = i * d2squareSize;
               float y = j * d2squareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x + 0.4 * d2squareSize;
               float SquareCenterY = y - 0.4 * d2squareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar2, counter2);
               if (isPointInside) {
                   alan8 += 1;
                   drawSquare(x, y, d2squareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }
       for (int i = 0; i < GRID_SIZE / 4; i++) {
           for (int j = 0; j < GRID_SIZE / 4; j++) {
               float x = i * d2squareSize;
               float y = j * d2squareSize; // Yüksekliði tersine çevirdik.


               float SquareCenterX = x + 0.4 * d2squareSize;
               float SquareCenterY = y - 0.4 * d2squareSize;
               int isPointInside = isPointInsideShape(SquareCenterX, SquareCenterY, kordinatlar3, counter3);
               if (isPointInside) {
                   alan8 += 1;
                   drawSquare(x, y, d2squareSize, 0.4f, 0.5f, 0.8f, 0.1f, BORDER_WIDTH_SMALL); // Þeklin içindeki kareleri farklý renkle boyama
               }




           }
       }


       drawObject(kordinatlar3, counter3);
       drawObject(kordinatlar2, counter2);
       drawObject(kordinatlar1, counter1);

       int total8 = alan8;
       int total4 = alan4 - alan8 * 4;
       int total2 = alan2 - alan4 * 4;
       int total1 = alan1 - alan2 * 4;

       int alan = total8+total4+total2+total1;
       return alan;



   }

   



int main(){
    int selection;
    printf("satir degerini girin: ");
    scanf_s("%d", &selection);
    
    //FILE* file;
    //char command[200] = "curl http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";
    //char buffer[1024];

    //if (fopen_s(&file, "output.txt", "w") != 0) {
    //    printf("Dosya açýlamadý.\n");
    //    return -1;
    //}

    // /*Komutun çýktýsýný dosyaya yaz*/
    //FILE* curl_output = _popen(command, "r");

    //if (curl_output == NULL) {
    //    printf("Komut çalýþtýrýlamadý.\n");
    //    fclose(file);
    //    remove("output.txt");
    //    return -1;
    //}

    //while (fgets(buffer, sizeof(buffer), curl_output) != NULL) {
    //    fprintf(file, "%s", buffer);
    //}

    //_pclose(curl_output); // Dosya iþaretçisini kapat
    //fclose(file); // Dosyayý kapat

   
    if (!glfwInit()) {
        fprintf(stderr, "Hata: GLFW baþlatýlamadý.\n");
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(2000, 2000, "Grid of Squares", NULL, NULL);
    if (!window) {
        glfwTerminate();
        fprintf(stderr, "Hata: Pencere oluþturulamadý.\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Hata: GLEW baþlatýlamadý.\n");
        return -1;
    }

    glViewport(10, 400, 1000, 1000);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);

  

    FILE* ile;
    fopen_s(&ile, "output.txt", "r"); // Dosyayý okuma modunda aç

    if (ile == NULL) {
        fprintf(stderr, "Dosya açýlamadý.\n");
        return -1;
    }

    char line[300] = { 0 };
   
    float kordinatlar[100][2] = { 0 };





    int index = 0;
    while (fgets(line, sizeof(line), ile) != NULL) {
        if (line[0] == '1' && selection == 1) {
            // Seçilen satýrýn içindeki koordinatlarý bul
            char* start = strchr(line, '(');
            while (start != NULL) {
                int x, y;
                if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                    kordinatlar[index][0] = x/64.0;
                    kordinatlar[index][1] = y/64.0;
                    index++;
                    start = strchr(start + 1, '(');
                }
                else {
                    start = NULL;
                }
            }
        }
        else if (line[0] == '2' && selection == 2) {
            // Seçilen satýrýn içindeki koordinatlarý bul
            char* start = strchr(line, '(');
            while (start != NULL) {
                int x, y;
                if (sscanf_s(start, "(%d,%d)", &x, &y) == 2) {
                    kordinatlar[index][0] = x/64.0;
                    kordinatlar[index][1] = y/64.0;
                    index++;
                    start = strchr(start + 1, '(');
                }
                else {
                    start = NULL;
                }
            }
        }
    }

    fclose(ile);




    float kordinatlar1[10][2] = { 0 };
    float kordinatlar2[10][2] = { 0 };

    int i = 0, j = 0;
    int counter1 = 0;
    int counter2 = 0;
    int flag = 0; // Kontrol bayraðý

    for (i = 0; i < 10; i++) {
        if (kordinatlar[i][0] == 0 && kordinatlar[i][1] == 0) {
            break; // 0,0'a gelindiðinde döngüyü durdur
        }

        if (flag == 0) {
            kordinatlar1[counter1][0] = kordinatlar[i][0];
            kordinatlar1[counter1][1] = kordinatlar[i][1];
            counter1++;

            for (int k = 0; k < counter1-1; k++) {
                if (kordinatlar[i][0] == kordinatlar[k][0] && kordinatlar[i][1] == kordinatlar[k][1]) {
                    flag = 1;
                   
                }
            }
        }
        else {
            kordinatlar2[counter2][0] = kordinatlar[i][0];
            kordinatlar2[counter2][1] = kordinatlar[i][1];
            counter2++;
        }
    }

 


    int alan;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Koyu mavi arkaplan rengi
        glClear(GL_COLOR_BUFFER_BIT);
        alan=drawGrid(selection);
 
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   

   

    glfwTerminate();

    printf("toplam alan %d \n", alan);
    printf("kaynak rezerv %d \n", alan*10);
    int maliyet;
    int platform;
    printf("birim sondaj maliyetini giriniz 1-10: ");
    scanf_s("%d", &maliyet);
    printf("birim platform maliyetini giriniz: ");
    scanf_s("%d", &platform);
    




    if (!glfwInit()) {
        fprintf(stderr, "Hata: GLFW baþlatýlamadý.\n");
        return -1;
    }

    GLFWwindow* window2;
    window2 = glfwCreateWindow(2000, 2000, "Grid of Squares", NULL, NULL);
    if (!window2) {
        glfwTerminate();
        fprintf(stderr, "Hata: Pencere oluþturulamadý.\n");
        return -1;
    }

    glfwMakeContextCurrent(window2);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Hata: GLEW baþlatýlamadý.\n");
        return -1;
    }

    glViewport(10, 400, 1000, 1000);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);


    int total=0;

    while (!glfwWindowShouldClose(window2)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // Koyu mavi arkaplan rengi
        glClear(GL_COLOR_BUFFER_BIT);
        total = drawGrid2(selection);


        glfwSwapBuffers(window2);
        glfwPollEvents();
    }


    printf("total platform  :%d\n",total);
    printf("total sondaj  :%d\n", alan);
    printf("toplam platform maliyet %d \n", platform*total);
    printf("toplam sondaj maliyet %d \n", maliyet* alan);
    printf("toplam  maliyet %d \n", maliyet* alan+ platform * total);
    printf("kar miktarý %d \n", alan * 10 - (maliyet * alan + platform * total));


   


    




    return 0;
}

