//
//  main.c
//  CG_finalProject
//
//  Created by NULL Pointers on 05/05/17.
//  Copyright © 2017 NULL Pointers. All rights reserved.
//

#include "glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
float SPEED = 30.0; // speed of traffic

float i = 0.0;     // movement of car
float m = 0.0;     // movement of clouds
float n = 0.0;     // movement of plane along x-axis
float o = 0.0;     //  and y-axis
float c = 0.0;     // movement of comet	SS
float angle = 0.0; // Angle of rotation for cloud

int light = 1; // 1 for green-light, 0 for red-light
int day = 1;   // 1 for day ,0 for night
int plane = 0; // 1 for plane
int comet = 0; // 1 for comet

GLboolean highspeed = false; // true for highspeed vehicles
GLboolean lowspeed = false;  // true for lowspeed vehicles
GLboolean right = true;      // The traffic moves from left to right

int flag = 0;
void *currentfont;

void setFont(void *font) { currentfont = font; }

void drawstring(float x, float y, float z, char *string) {
  char *c;
  glRasterPos3f(x, y, z);

  for (c = string; *c != '\0'; c++) {
    glColor3f(0.0, 0.0, 0.0);
    glutBitmapCharacter(currentfont, *c);
  }
}

void draw_pixel(GLint cx, GLint cy) {

  glBegin(GL_POINTS);
  glVertex2i(cx, cy);
  glEnd();
}

void plotpixels(GLint h, GLint k, GLint x, GLint y) {
  draw_pixel(x + h, y + k);
  draw_pixel(-x + h, y + k);
  draw_pixel(x + h, -y + k);
  draw_pixel(-x + h, -y + k);
  draw_pixel(y + h, x + k);
  draw_pixel(-y + h, x + k);
  draw_pixel(y + h, -x + k);
  draw_pixel(-y + h, -x + k);
}

void draw_circle(GLint h, GLint k, GLint r) {
  GLint d = 1 - r, x = 0, y = r;
  while (y > x) {
    plotpixels(h, k, x, y);
    if (d < 0)
      d += 2 * x + 3;
    else {
      d += 2 * (x - y) + 5;
      --y;
    }
    ++x;
  }
  plotpixels(h, k, x, y);
}

void draw_object() {
  int l;
  if (day == 1) {
    // sky
    glColor3f(0.0, 0.9, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(0, 450);
    glVertex2f(0, 700);
    glVertex2f(1100, 700);
    glVertex2f(1100, 450);
    glEnd();

    // sun
    glPushMatrix();
    glTranslatef(100, 625, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-100, -625, 0);
    for (l = 0; l <= 35; l++) {
      glColor3f(1.0, 0.7, 0.1);
      draw_circle(100, 625, l);
    }
    glPopMatrix();

    // plane
    if (plane == 1) {
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
      glVertex2f(925 + n, 625 + o);
      glVertex2f(950 + n, 640 + o);
      glVertex2f(1015 + n, 640 + o);
      glVertex2f(1030 + n, 650 + o);
      glVertex2f(1050 + n, 650 + o);
      glVertex2f(1010 + n, 625 + o);
      glEnd();

      glColor3f(0.8, 0.8, 0.8);
      glBegin(GL_LINE_LOOP);
      glVertex2f(925 + n, 625 + o);
      glVertex2f(950 + n, 640 + o);
      glVertex2f(1015 + n, 640 + o);
      glVertex2f(1030 + n, 650 + o);
      glVertex2f(1050 + n, 650 + o);
      glVertex2f(1010 + n, 625 + o);
      glEnd();
    }

    // cloud1
    glPushMatrix();
    glTranslatef(170 + m, 625, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-170 - m, -625, 0);
    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(160 + m, 625, l);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(195 + m, +625, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-200 - m, -625, 0);
    for (l = 0; l <= 35; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(195 + m, 625, l);
      //   draw_circle(225 + m, 625, l)
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(235 + m, 625, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-230 - m, -625, 0);

    for (l = 0; l <= 35; l++) {
      glColor3f(1.0, 1.0, 1.0);
      // draw_circle(200 + m, 625, l);
      draw_circle(225 + m, 625, l);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(245 + m, 625, 0);
    glRotatef(-angle + 80, 0.0, 0.0, 1.0);
    glTranslatef(-245 - m, -625, 0);
    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(265 + m, 625, l);
    }
    glPopMatrix();

    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(160 + m, 625, l);
    }
    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(265 + m, 625, l);
    }

    // cloud2
    glPushMatrix();
    glTranslatef(380 + m, 615, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-380 - m, -615, 0);
    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(370 + m, 615, l);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(410 + m, +615, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-405 - m, -615, 0);
    for (l = 0; l <= 35; l++) {

      glColor3f(1.0, 1.0, 1.0);
      draw_circle(410 + m, 615, l);
      // draw_circle(435 + m, 615, l);
      // draw_circle(470 + m, 615, l);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(435 + m, 615, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-433 - m, -615, 0);
    for (l = 0; l <= 35; l++) {

      glColor3f(1.0, 1.0, 1.0);
      // draw_circle(410 + m, 615, l);
      draw_circle(435 + m, 615, l);
      // draw_circle(470 + m, 615, l);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(470 + m, 615, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-468 - m, -615, 0);
    for (l = 0; l <= 35; l++) {

      glColor3f(1.0, 1.0, 1.0);
      // draw_circle(410 + m, 615, l);
      //   draw_circle(435 + m, 615, l);
      draw_circle(470 + m, 615, l);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(490 + m, 615, 0);
    glRotatef(-angle + 80, 0.0, 0.0, 1.0);
    glTranslatef(-490 - m, -615, 0);
    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(500 + m, 615, l);
    }
    glPopMatrix();

    for (l = 0; l <= 20; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(370 + m, 615, l);
      draw_circle(500 + m, 615, l);
    }

    // grass
    glColor3f(0.9, 0.5, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(0, 160);
    glVertex2f(0, 450);
    glVertex2f(1100, 450);
    glVertex2f(1100, 160);
    glEnd();

    // pond
    glColor3f(0.0, 0.9, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(25, 350);
    glVertex2f(25, 375);
    glVertex2f(50, 400);
    glVertex2f(75, 410);
    glVertex2f(100, 420);
    glVertex2f(200, 420);
    glVertex2f(225, 410);
    glVertex2f(250, 405);
    glVertex2f(275, 390);
    glVertex2f(300, 375);
    glVertex2f(310, 350);
    glVertex2f(300, 320);
    glVertex2f(275, 300);
    glVertex2f(250, 295);
    glVertex2f(225, 290);
    glVertex2f(200, 285);
    glVertex2f(175, 280);
    glVertex2f(150, 280);
    glVertex2f(125, 280);
    glVertex2f(100, 290);
    glVertex2f(75, 300);
    glVertex2f(50, 310);
    glEnd();

  }

  else {

    // sky
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 450);
    glVertex2f(0, 700);
    glVertex2f(1100, 700);
    glVertex2f(1100, 450);
    glEnd();

    // moon
    int l;
    glPushMatrix();
    glTranslatef(100, 625, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-100, -625, 0);
    for (l = 0; l <= 35; l++) {
      glColor3f(1.0, 1.0, 1.0);
      draw_circle(100, 625, l);
    }
    glPopMatrix();

    // star1
    glPushMatrix();
    glTranslatef(575, 647, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-575, -647, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(575, 653);
    glVertex2f(570, 645);
    glVertex2f(580, 645);
    glVertex2f(575, 642);
    glVertex2f(570, 650);
    glVertex2f(580, 650);
    glEnd();
    glPopMatrix();

    // star2
    glPushMatrix();
    glTranslatef(975, 637, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-975, -637, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(975, 643);
    glVertex2f(970, 635);
    glVertex2f(980, 635);
    glVertex2f(975, 632);
    glVertex2f(970, 640);
    glVertex2f(980, 640);
    glEnd();
    glPopMatrix();

    // star3
    glPushMatrix();
    glTranslatef(875, 537, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-875, -537, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(875, 543);
    glVertex2f(870, 535);
    glVertex2f(880, 535);
    glVertex2f(875, 532);
    glVertex2f(870, 540);
    glVertex2f(880, 540);
    glEnd();
    glPopMatrix();

    // star4
    glPushMatrix();
    glTranslatef(375, 593, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-375, -593, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(375, 598);
    glVertex2f(370, 590);
    glVertex2f(380, 590);
    glVertex2f(375, 587);
    glVertex2f(370, 595);
    glVertex2f(380, 595);
    glEnd();
    glPopMatrix();

    // star5
    glPushMatrix();
    glTranslatef(750, 623, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-750, -623, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(750, 628);
    glVertex2f(745, 620);
    glVertex2f(755, 620);
    glVertex2f(750, 618);
    glVertex2f(745, 625);
    glVertex2f(755, 625);
    glEnd();
    glPopMatrix();

    // star6
    glPushMatrix();
    glTranslatef(200, 623, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-200, -623, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(200, 628);
    glVertex2f(195, 620);
    glVertex2f(205, 620);
    glVertex2f(200, 618);
    glVertex2f(195, 625);
    glVertex2f(205, 625);
    glEnd();
    glPopMatrix();

    // star7
    glPushMatrix();
    glTranslatef(500, 537, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(-500, -537, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(500, 543);
    glVertex2f(495, 535);
    glVertex2f(505, 535);
    glVertex2f(500, 532);
    glVertex2f(495, 540);
    glVertex2f(505, 540);
    glEnd();
    glPopMatrix();

    // comet
    if (comet == 1) {
      for (l = 0; l <= 7; l++) {
        glColor3f(1.0, 1.0, 1.0);
        draw_circle(300 + c, 675, l);
      }

      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_TRIANGLES);
      glVertex2f(200 + c, 675);
      glVertex2f(300 + c, 682);
      glVertex2f(300 + c, 668);
      glEnd();
    }

    // Plane
    if (plane == 1) {

      for (l = 0; l <= 1; l++) {
        glColor3f(1.0, 0.0, 0.0);
        draw_circle(950 + n, 625 + o, l);
        glColor3f(1.0, 1.0, 0.0);
        draw_circle(954 + n, 623 + o, l);
      }
    }

    // grass
    glColor3f(0.8, 0.3, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0, 160);
    glVertex2f(0, 450);
    glVertex2f(1100, 450);
    glVertex2f(1100, 160);
    glEnd();

    // pond
    glColor3f(0.1, 0.2, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(25, 350);
    glVertex2f(25, 375);
    glVertex2f(50, 400);
    glVertex2f(75, 410);
    glVertex2f(100, 420);
    glVertex2f(200, 420);
    glVertex2f(225, 410);
    glVertex2f(250, 405);
    glVertex2f(275, 390);
    glVertex2f(300, 375);
    glVertex2f(310, 350);
    glVertex2f(300, 320);
    glVertex2f(275, 300);
    glVertex2f(250, 295);
    glVertex2f(225, 290);
    glVertex2f(200, 285);
    glVertex2f(175, 280);
    glVertex2f(150, 280);
    glVertex2f(125, 280);
    glVertex2f(100, 290);
    glVertex2f(75, 300);
    glVertex2f(50, 310);
    glEnd();
  }

  // road boundary
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(0, 150);
  glVertex2f(0, 160);
  glVertex2f(1100, 160);
  glVertex2f(1100, 150);
  glEnd();

  // road
  glColor3f(0.2, 0.2, 0.2);
  glBegin(GL_POLYGON);
  glVertex2f(0, 0);
  glVertex2f(0, 150);
  glVertex2f(1100, 150);
  glVertex2f(1100, 0);
  glEnd();

  // tree
  glColor3f(0.9, 0.2, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(350, 325);
  glVertex2f(350, 395);
  glVertex2f(365, 395);
  glVertex2f(365, 325);
  glEnd();

  for (l = 0; l <= 30; l++) {
    glColor3f(0.0, 0.5, 0.0);
    draw_circle(340, 400, l);
    draw_circle(380, 400, l);
  }

  for (l = 0; l <= 25; l++) {
    glColor3f(0.0, 0.5, 0.0);
    draw_circle(350, 440, l);
    draw_circle(370, 440, l);
  }

  for (l = 0; l <= 20; l++) {
    glColor3f(0.0, 0.5, 0.0);
    draw_circle(360, 465, l);
  }

  // back compound
  glColor3f(0.9, 0.9, 0.9);
  glBegin(GL_POLYGON);
  glVertex2f(550, 375);
  glVertex2f(600, 425);
  glVertex2f(825, 425);
  glVertex2f(850, 375);
  glEnd();

  // house
  glColor3f(0.0, 0.2, 0.2);
  glBegin(GL_POLYGON);
  glVertex2f(600, 375);
  glVertex2f(600, 450);
  glVertex2f(650, 525);
  glVertex2f(700, 450);
  glVertex2f(700, 375);
  glEnd();

  // door
  glColor3f(0.5, 0.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex2f(640, 375);
  glVertex2f(640, 410);
  glVertex2f(660, 410);
  glVertex2f(660, 375);
  glEnd();

  // roof
  glColor3f(0.5, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(700, 450);
  glVertex2f(650, 525);
  glVertex2f(750, 525);
  glVertex2f(780, 450);
  glEnd();

  //
  glColor3f(0.8, 0.8, 0.2);
  glBegin(GL_POLYGON);
  glVertex2f(700, 375);
  glVertex2f(700, 450);
  glVertex2f(780, 450);
  glVertex2f(780, 375);
  glEnd();

  // window
  glColor3f(0.5, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(725, 400);
  glVertex2f(725, 420);
  glVertex2f(740, 420);
  glVertex2f(740, 400);
  glEnd();

  // compound
  glColor3f(0.7, 0.7, 0.7);
  glBegin(GL_POLYGON);
  glVertex2f(550, 325);
  glVertex2f(550, 375);
  glVertex2f(850, 375);
  glVertex2f(850, 325);
  glEnd();

  // gate using mesh
  int a, b;
  float x[3], y[3];
  float x0 = 600, y0 = 325;
  ;

  glColor3f(0.0, 0.0, 0.0);
  for (a = 0; a < 3; a++)
    x[a] = x0 + a * 25;

  for (b = 0; b < 3; b++)
    y[b] = y0 + b * 25;

  for (a = 0; a < 2; a++)
    for (b = 0; b < 2; b++) {
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINE_LOOP);
      glVertex2f(x[a], y[b]);
      glVertex2f(x[a], y[b + 1]);
      glVertex2f(x[a + 1], y[b + 1]);
      glVertex2f(x[a + 1], y[b]);
      glEnd();
    }
  // When the direction of the traffic is default
  if (right == true) {

    // Zebra Crossing
    glColor3f(1, 1, 1);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(1060, 140);
    glVertex2i(1100, 140);
    glVertex2i(1060, 130);
    glVertex2i(1100, 130);
    glVertex2i(1060, 120);
    glVertex2i(1100, 120);
    glVertex2i(1100, 110);
    glVertex2i(1060, 110);
    glVertex2i(1060, 100);
    glVertex2i(1100, 100);
    glVertex2i(1060, 90);
    glVertex2i(1100, 90);
    glVertex2i(1060, 80);
    glVertex2i(1100, 80);
    glVertex2i(1060, 70);
    glVertex2i(1100, 70);
    glVertex2i(1060, 60);
    glVertex2i(1100, 60);
    glVertex2i(1060, 50);
    glVertex2i(1100, 50);
    glVertex2i(1060, 40);
    glVertex2i(1100, 40);
    glVertex2i(1060, 30);
    glVertex2i(1100, 30);
    glVertex2i(1060, 20);
    glVertex2i(1100, 20);
    glVertex2i(1060, 10);
    glVertex2i(1100, 10);
    glVertex2i(1060, 00);
    glVertex2i(1100, 00);
    glEnd();

    // signal
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1060, 160);
    glVertex2f(1060, 350);
    glVertex2f(1070, 350);
    glVertex2f(1070, 160);
    glEnd();

    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(1040, 350);
    glVertex2f(1040, 500);
    glVertex2f(1090, 500);
    glVertex2f(1090, 350);
    glEnd();

    for (l = 0; l <= 20; l++) {
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(1065, 475, l);
      glColor3f(1.0, 1.0, 0.0);
      draw_circle(1065, 425, l);
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(1065, 375, l);
    }

    // car 1
    glColor3f(0.9, 0.2, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(25 + i, 50);
    glVertex2f(25 + i, 125);
    glVertex2f(75 + i, 200);
    glVertex2f(175 + i, 200);
    glVertex2f(200 + i, 125);
    glVertex2f(250 + i, 115);
    glVertex2f(250 + i, 50);
    glEnd();

    // windows
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(35 + i, 125);
    glVertex2f(80 + i, 190);
    glVertex2f(115 + i, 190);
    glVertex2f(115 + i, 125);
    glEnd();

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(125 + i, 125);
    glVertex2f(125 + i, 190);
    glVertex2f(170 + i, 190);
    glVertex2f(190 + i, 125);
    glEnd();

    for (l = 0; l < 20; l++) {
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(75 + i, 50, l);
      draw_circle(175 + i, 50, l);
    }

    // car2

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-470 + i, 50);
    glVertex2f(-470 + i, 112);
    glVertex2f(-400 + i, 125);
    glVertex2f(-372 + i, 210);
    glVertex2f(-210 + i, 210);
    glVertex2f(-180 + i, 125);
    glVertex2f(-135 + i, 125);
    glVertex2f(-110 + i, 50);
    glEnd();

    // windows
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-410 + i, 125);
    glVertex2f(-364 + i, 200);
    glVertex2f(-300 + i, 200);
    glVertex2f(-300 + i, 125);
    glEnd();

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-290 + i, 125);
    glVertex2f(-290 + i, 200);
    glVertex2f(-217 + i, 200);
    glVertex2f(-192 + i, 125);
    glEnd();

    for (l = 0; l < 30; l++) {
      glColor3f(0.1, 0.1, 0.1);
      draw_circle(-350 + i, 50, l);
      draw_circle(-200 + i, 50, l);
    }

    // bus

    glColor3f(0.6, 0.3, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(350 + i, 50);
    glVertex2f(350 + i, 275);
    glVertex2f(722 + i, 275);
    glVertex2f(750 + i, 175);
    glVertex2f(750 + i, 50);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(650 + i, 175);
    glVertex2f(650 + i, 260);
    glVertex2f(720 + i, 260);
    glVertex2f(745 + i, 175);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(550 + i, 175);
    glVertex2f(550 + i, 260);
    glVertex2f(625 + i, 260);
    glVertex2f(625 + i, 175);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(450 + i, 175);
    glVertex2f(450 + i, 260);
    glVertex2f(525 + i, 260);
    glVertex2f(525 + i, 175);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(375 + i, 175);
    glVertex2f(375 + i, 260);
    glVertex2f(425 + i, 260);
    glVertex2f(425 + i, 175);
    glEnd();

    for (l = 0; l < 30; l++) {
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(450 + i, 50, l);
      draw_circle(625 + i, 50, l);
    }

  }
  // When the direction of the traffic is reversed
  else {

    // Zebra Crossing
    glColor3f(1, 1, 1);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(1100 - 1060, 140);
    glVertex2i(1100 - 1100, 140);
    glVertex2i(1100 - 1060, 130);
    glVertex2i(1100 - 1100, 130);
    glVertex2i(1100 - 1060, 120);
    glVertex2i(1100 - 1100, 120);
    glVertex2i(1100 - 1100, 110);
    glVertex2i(1100 - 1060, 110);
    glVertex2i(1100 - 1060, 100);
    glVertex2i(1100 - 1100, 100);
    glVertex2i(1100 - 1060, 90);
    glVertex2i(1100 - 1100, 90);
    glVertex2i(1100 - 1060, 80);
    glVertex2i(1100 - 1100, 80);
    glVertex2i(1100 - 1060, 70);
    glVertex2i(1100 - 1100, 70);
    glVertex2i(1100 - 1060, 60);
    glVertex2i(1100 - 1100, 60);
    glVertex2i(1100 - 1060, 50);
    glVertex2i(1100 - 1100, 50);
    glVertex2i(1100 - 1060, 40);
    glVertex2i(1100 - 1100, 40);
    glVertex2i(1100 - 1060, 30);
    glVertex2i(1100 - 1100, 30);
    glVertex2i(1100 - 1060, 20);
    glVertex2i(1100 - 1100, 20);
    glVertex2i(1100 - 1060, 10);
    glVertex2i(1100 - 1100, 10);
    glVertex2i(1100 - 1060, 00);
    glVertex2i(1100 - 1100, 00);
    glEnd();

    // signal
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1100 - 1060, 160);
    glVertex2f(1100 - 1060, 350);
    glVertex2f(1100 - 1070, 350);
    glVertex2f(1100 - 1070, 160);
    glEnd();

    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    glVertex2f(1100 - 1040, 350);
    glVertex2f(1100 - 1040, 500);
    glVertex2f(1100 - 1090, 500);
    glVertex2f(1100 - 1090, 350);
    glEnd();

    for (l = 0; l <= 20; l++) {
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(1100 - 1065, 475, l);
      glColor3f(1.0, 1.0, 0.0);
      draw_circle(1100 - 1065, 425, l);
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(1100 - 1065, 375, l);
    }

    // car 1
    glColor3f(0.9, 0.2, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1100 - 25 + i, 50);
    glVertex2f(1100 - 25 + i, 125);
    glVertex2f(1100 - 75 + i, 200);
    glVertex2f(1100 - 175 + i, 200);
    glVertex2f(1100 - 200 + i, 125);
    glVertex2f(1100 - 250 + i, 115);
    glVertex2f(1100 - 250 + i, 50);
    glEnd();

    // windows
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(1100 - 35 + i, 125);
    glVertex2f(1100 - 80 + i, 190);
    glVertex2f(1100 - 115 + i, 190);
    glVertex2f(1100 - 115 + i, 125);
    glEnd();

    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(1100 - 125 + i, 125);
    glVertex2f(1100 - 125 + i, 190);
    glVertex2f(1100 - 170 + i, 190);
    glVertex2f(1100 - 190 + i, 125);
    glEnd();

    for (l = 0; l < 20; l++) {
      glColor3f(0.0, 0.0, 0.0);
      draw_circle(75 + i, 50, l);
      draw_circle(175 + i, 50, l);
    }
  }

  glFlush();
}

void traffic_light() {
  int l;
  if (right == true) {
    if (light == 1) {
      for (l = 0; l <= 20; l++) {

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1065, 475, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1065, 425, l);

        glColor3f(0.0, 0.7, 0.0);
        draw_circle(1065, 375, l);
      }
    }

    else if (light == 2) {

      for (l = 0; l <= 20; l++) {
        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1065, 475, l);

        glColor3f(1.0, 1.0, 0.0);
        draw_circle(1065, 425, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1065, 375, l);
      }
    } else {
      for (l = 0; l <= 20; l++) {
        glColor3f(1.0, 0.0, 0.0);
        draw_circle(1065, 475, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1065, 425, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1065, 375, l);
      }
    }
    // When the traffic moves the other way
  } else {
    if (light == 1) {
      for (l = 0; l <= 20; l++) {

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 475, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 425, l);

        glColor3f(0.0, 0.7, 0.0);
        draw_circle(1100 - 1065, 375, l);
      }
    }

    else if (light == 2) {

      for (l = 0; l <= 20; l++) {
        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 475, l);

        glColor3f(1.0, 1.0, 0.0);
        draw_circle(1100 - 1065, 425, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 375, l);
      }
    } else {
      for (l = 0; l <= 20; l++) {
        glColor3f(1.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 475, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 425, l);

        glColor3f(0.0, 0.0, 0.0);
        draw_circle(1100 - 1065, 375, l);
      }
    }
  }
}

void idle() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  angle += 1.0;
  if ((light == 0 || light == 2) &&
      (i >= 330 &&
       i <= 750)) // value of i when first vehicle is near the traffic-signal
  {

    i += SPEED / 10;
    ++m;
    n -= 2;
    o += 0.2;
    c += 2;
  }

  if ((light == 0 || light == 2) &&
      (i >= 830 &&
       i <= 1100)) // value of i when second vehicle is near the traffic-signal
  {

    i += SPEED / 10;
    ++m;
    n -= 2;
    o += 0.2;
    c += 2;
  }

  if ((light == 0 || light == 2) &&
      (i >= 1200 &&
       i <= 1620)) // value of i when third vehicle is near the traffic signal
  {

    i += SPEED / 10;
    ++m;
    n -= 2;
    o += 0.2;
    c += 2;
  }

  if ((light == 0 || light == 2)) {
    i = i;
    ++m;
    n -= 2;
    o += 0.2;
    c += 2;

  }

  else {

    i += SPEED / 10;
    ++m;
    n -= 2;
    o += 0.2;
    c += 2;
  }
  if (i > 1630)
    i = 0.0;
  if (m > 1100)
    m = 0.0;
  if (o > 75) {
    plane = 0;
  }
  if (c > 500) {
    comet = 0;
  }
  glutPostRedisplay();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (flag == 0) {
    // START SCREEN
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glClearColor(0.15, 0.1, 0.01, 0); /*background for cover page*/
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    drawstring(350.0, 650.0, 0.0,
               "REVA INSTITUTE OF TECHNOLOGY AND MANAGEMENT");
    glColor3f(0.7, 0, 1);
    drawstring(450, 600, 0.0, "DEPARTMENT OF C AND IT");
    glColor3f(1, 0.5, 0);
    drawstring(420, 550, 0.0, "COMPUTER GRAPHIC PROJECT ON");
    glColor3f(1, 0, 0);
    drawstring(440, 500, 0.0, "TRAFFIC SIGNAL SIMULATION");
    glColor3f(1, 0.5, 0);
    drawstring(200, 400, 0.0, "BY:");
    glColor3f(1, 1, 1);
    drawstring(100, 300, 0.0, "UJWAL P  (1RE14CS125)");
    glColor3f(1, 1, 1);
    drawstring(100, 240, 0.0, "K SAI SOMANATH   (1RE14CS126)");
    glColor3f(1, 0.5, 0);
    drawstring(850, 400, 0.0, "GUIDES:");
    glColor3f(1, 1, 1);
    drawstring(750, 300, 0.0, "Prof. NAVEEN CHANDRA GOWDA");
    glColor3f(1, 1, 1);
    drawstring(750, 240, 0.0, "Prof. CHAITHRA M H");
    glColor3f(1, 0.1, 1);
    drawstring(450, 100, 0.0, "PRESS ENTER TO START");
    glFlush();
  } else if (flag == 1) {
    // HELP SCREEN
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glClearColor(0, 0, 0, 0); /*background for cover page*/
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    drawstring(550.0, 700.0, 0.0, "TIPS");
    glColor3f(1, 0, 0);
    drawstring(650.0, 700.0, 0.0, "AND");
    glColor3f(0, 0, 1);
    drawstring(750.0, 700.0, 0.0, "TRICKS");
    glColor3f(0.5, 0.1, 0.2);
    drawstring(350.0, 640.0, 0.0,
               "Stop the traffic (Red Light)                                  "
               "PRESS 'r' or 'R'");
    glColor3f(0.5, 0.1, 0.3);
    drawstring(350.0, 540.0, 0.0,
               "Yellow Signal                                                  "
               "      PRESS 'y' or 'Y'");
    glColor3f(0.5, 0.1, 0.4);
    drawstring(350.0, 440.0, 0.0,
               "Green Signal                                                   "
               "      PRESS 'g' or 'G'");
    glColor3f(0.4, 0.1, 0.5);
    drawstring(350.0, 340.0, 0.0,
               "Inc or Dec speed                                               "
               "   PRESS '+' or '-'");
    glColor3f(0.5, 0.1, 0.6);
    drawstring(350.0, 240.0, 0.0,
               "Day or Night                                                   "
               "      PRESS 'd' or 'n'");
    glColor3f(0.5, 0.1, 0.7);
    drawstring(350.0, 140.0, 0.0,
               "Menu                                                           "
               "         MOUSE RIGHT BUTTON");
    glColor3f(0.5, 0.1, 0.8);
    drawstring(350.0, 90.0, 0.0,
               "Help                                                           "
               "           PRESS 'h' or 'H'");
    glColor3f(0.5, 0.1, 0.9);
    drawstring(350.0, 40.0, 0.0,
               "Escape                                                         "
               "         PRESS 'ENTER'");
    glFlush();
  } else if (flag == 2) {

    // MAIN SCREEN
    draw_object();
    traffic_light();
    if (highspeed) {
      setFont(GLUT_BITMAP_TIMES_ROMAN_24);
      glColor3f(1, 0, 0);
      drawstring(400.0, 200.0, 0.0, "Warning! High Speed Alert!!");
    }
    if (lowspeed) {
      setFont(GLUT_BITMAP_TIMES_ROMAN_24);
      glColor3f(1, 0, 0);
      drawstring(400.0, 200.0, 0.0,
                 "Warning! Do not stop vehicle in running traffic!!");
    }
  }
  glFlush();
  glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y) {
  switch (key) {
  case 13:
    if (flag == 1) {
      flag = 2;
      display();
    }
    if (flag == 0) {
      flag = 1;
      display();
    }
    break;
  case 'g':
  case 'G':
    light = 1;
    break;

  case 'r':
  case 'R':
    light = 0;
    break;

  case 'd':
  case 'D':
    day = 1;
    break;

  case 'n':
  case 'N':
    day = 0;
    break;
  case 'y':
  case 'Y':
    light = 2;
    break;
  case 'l':
  case 'L':
    right = false;
    break;

  case '+':
    if (SPEED < 80) {
      highspeed = false;
      lowspeed = false;
      SPEED = SPEED + 10;
    } else
      highspeed = true;
    break;

  case '-':
    if (SPEED > 10) {
      lowspeed = false;
      highspeed = false;
      SPEED = SPEED - 10;
    } else
      lowspeed = true;
    break;

  case 'h':
    flag = 1;
    display();
    break;

  case 'q':
  case 'Q':
    exit(0);
    break;
  }
}

void main_menu(int index) {
  switch (index) {
  case 1:
    if (index == 1) {
      plane = 1;
      o = n = 0.0;
    }
    break;

  case 2:
    if (index == 2) {
      comet = 1;
      c = 0.0;
    }
    break;

  case 3:
    if (index == 3) {
      SPEED = 10.0;
    }
    break;

  case 4:
    if (index == 4) {
      SPEED = 20.0;
    }
    break;

  case 5:
    if (index == 5) {
      SPEED = 30.0;
    }
    break;

  case 6:
    if (index == 6) {
      SPEED = 40.0;
    }
    break;
  }
}

void myinit() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(0.0, 0.0, 1.0);
  glPointSize(2.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1100.0, 0.0, 700.0);
}

int main(int argc, char **argv) {
  int c_menu;
  printf("Press 'r' or 'R' to change the signal light to red \n");
  printf("Press 'g' or 'G' to change the signal light to green \n");
  printf("Press 'y' or 'Y' to change the signal to yellow \n");

  printf("Press 'd' or 'D' to make it day \n");
  printf("Press 'n' or 'N' to make it night \n");

  printf("Press '+' to increase the speed \n");
  printf("Press '-' to increase the speed \n");
  printf("Press 'q' or 'Q' to quit the program \n");

  printf("Press RIGHT MOUSE BUTTON to display menu , the whole image is paused "
         "until the menu is selected \n");

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(2000.0, 1100.0);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Traffic Control");
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboardFunc);
  myinit();

  // create a sub menu to change speed
  int subMenu = glutCreateMenu(main_menu);
  glutAddMenuEntry("10", 3);
  glutAddMenuEntry("20", 4);
  glutAddMenuEntry("30", 5);
  glutAddMenuEntry("40", 6);

  c_menu = glutCreateMenu(main_menu);
  glutAddSubMenu("Speed", subMenu);
  glutAddMenuEntry("Aeroplane", 1);
  glutAddMenuEntry("Comet", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}
