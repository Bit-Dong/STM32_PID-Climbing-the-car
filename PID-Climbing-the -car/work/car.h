#ifndef _CAR_H
#define _CAR_H

void GPIOB_Init(void);
void forward(int t);
void back(int t);
void turn_left(int t_l,int t_r);
void turn_right(int t_l,int t_r);
void stop(void);

#endif

