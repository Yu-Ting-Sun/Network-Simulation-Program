#include<stdio.h>
#include<stdlib.h>
#include <time.h> 
#include <math.h> 

 
struct Road
{
    int entrance;
    int direction;
    int location_x;
    int location_y;
};

struct Car
{
    int d_x;
    int d_y;
    int exist;
    int location_x;
    int location_y;
    int call;
    double max_power;
    int cell;
    int call_time;
};

struct Cell
{
    int location_x;
    int location_y;
    int freq;
    int exist;
};
int change_time = 0;
int car_count = 0;
int call_count = 0;
double distance = 0;
double power = 0;
int check = 0; 
int mode = 0;
struct Road road[121];
struct Car car[2000];
struct Cell cell[20];
int random_cell();
int random_call();
int random_direction();
int random_entrance();
int random_offset();
void cell_build();
void road_build();
void turn();
void car_in();
void car_go_and_out();
void call();
void best();
void minium();
void entropy();
void mine();
double pathloss(int freq, double distance);
double dist( double x1, double y1, double x2, double y2 );
int gaussrand();
int random_freq();
int main(){
    srand( time(NULL) );   
    for(int j = 0;j < 2000; j++){
        car[j].call = 0;
        car[j].exist = 0;
        car[j].max_power = 15;
        car[j].call_time = 0;
        car[j].location_x = 0;
        car[j].location_y = 0;
    }
    for(int j = 0;j < 20; j++){
        cell[j].exist = 0;
        cell[j].freq = 0;
    }
    cell_build();
    road_build();
    FILE *fp = NULL ;
    fp = fopen("result.xls","w") ;
    fprintf(fp,"Algorithm\tchange time\tcar\tcall\n") ;    
    fclose(fp);

    //best循環開始
    for(int a = 0; a < 3600; a++){
        car_in();
        turn();
        car_go_and_out();
        call();
        best();
        for(int i = 0; i < 2000; i++){
            if(car[i].exist){
                car_count++;
            }
            if(car[i].call){
                call_count++;
            }
        }

        FILE *fp = NULL ;
        fp = fopen("result.xls","a") ;
        //for (int b=0 ; b<3600 ;b++)
        fprintf(fp,"BEST\t%d\t%d\t%d\n",change_time,car_count,call_count ) ;
        fclose(fp);
        car_count = 0;
        call_count = 0;           

    }
    printf("BEST:%d\n",change_time);

    for(int j = 0;j < 2000; j++){
        car[j].call = 0;
        car[j].exist = 0;
        car[j].max_power = 15;
        car[j].call_time = 0;
        car[j].location_x = 0;
        car[j].location_y = 0;            
    }

    change_time = 0;
    //minium循環開始
    for(int a = 0; a < 3600; a++){
        car_in();
        turn();
        car_go_and_out();
        call();
        minium();
        for(int i = 0; i < 2000; i++){
            if(car[i].exist){
                car_count++;
            }
            if(car[i].call){
                call_count++;
            }
        }

        FILE *fp = NULL ;
        fp = fopen("result.xls","a") ;
        //for (int b=0 ; b<3600 ;b++)
        fprintf(fp,"MINIUM\t%d\t%d\t%d\n",change_time,car_count,call_count ) ;
        fclose(fp);
        car_count = 0;
        call_count = 0;           

    }
    printf("MINIUM:%d\n",change_time);

    for(int j = 0;j < 2000; j++){
        car[j].call = 0;
        car[j].exist = 0;
        car[j].max_power = 15;
        car[j].call_time = 0;
        car[j].location_x = 0;
        car[j].location_y = 0;        
    }

    change_time = 0;
    //entropy循環開始
    for(int a = 0; a < 3600; a++){
        car_in();
        turn();
        car_go_and_out();
        call();
        entropy();
        for(int i = 0; i < 2000; i++){
            if(car[i].exist){
                car_count++;
            }
            if(car[i].call){
                call_count++;
            }
        }

        FILE *fp = NULL ;
        fp = fopen("result.xls","a") ;
        //for (int b=0 ; b<3600 ;b++)
        fprintf(fp,"ENTROPY\t%d\t%d\t%d\n",change_time,car_count,call_count ) ;
        fclose(fp);
        car_count = 0;
        call_count = 0;           

    }
    printf("ENTROPY:%d\n",change_time);

    for(int j = 0;j < 2000; j++){
        car[j].call = 0;
        car[j].exist = 0;
        car[j].max_power = 15;
        car[j].call_time = 0;
        car[j].location_x = 0;
        car[j].location_y = 0;        
    }

    change_time = 0;
    //mine循環開始
    for(int a = 0; a < 3600; a++){
        car_in();
        turn();
        car_go_and_out();
        call();
        mine();
        for(int i = 0; i < 2000; i++){
            if(car[i].exist){
                car_count++;
            }
            if(car[i].call){
                call_count++;
            }
        }

        FILE *fp = NULL ;
        fp = fopen("result.xls","a") ;
        //for (int b=0 ; b<3600 ;b++)
        fprintf(fp,"MINE\t%d\t%d\t%d\n",change_time,car_count,call_count ) ;
        fclose(fp);
        car_count = 0;
        call_count = 0;           

    }
    printf("MINE:%d\n",change_time);    


    return 0;
}

int random_cell(){//10%機率為1(每格有cell的機率)
    //int x = rand() % (max - min + 1) + min;
    int flag;
    int x = rand() % 10 + 1;   

    if(x == 1){
        flag = 1;
    }
    else{
        flag = 0;
    }

    return flag;
}

int random_freq(){//cell頻率機率
    //int x = rand() % (max - min + 1) + min;
    int x = rand() % 10 + 1;   

    return x * 100;
}

int random_offset(){//cell各方向偏移的機率
    //int x = rand() % (max - min + 1) + min;
    int flag;
    int x = rand() % 4 + 1;   

    if(x == 1){
        flag = 1;
    }
    else if(x == 2){
        flag = 2;
    }
    else if(x == 3){
        flag = 3;
    }
    else{
        flag = 4;
    }

    return flag;
}

void cell_build(){//決定cell位置
    for (int i = 0; i < 100; i++){
        if(random_cell()){
            for(int j = 0;j < 20; j++){
                if(cell[j].exist == 0){
                    cell[j].exist = 1;
                    //printf("%d: %d\n",j, cell[j].exist);
                    cell[j].freq = random_freq();
                    if(random_offset() == 1){
                        cell[j].location_x = 2500 * (i % 10) + 1250;
                        cell[j].location_y = 2500 * (i / 10) + 1150;
                    }
                    else if(random_offset() == 2){
                        cell[j].location_x = 2500 * (i % 10) + 1250;
                        cell[j].location_y = 2500 * (i / 10) + 1350;
                    }  
                    else if(random_offset() == 3){
                        cell[j].location_x = 2500 * (i % 10) + 1150;
                        cell[j].location_y = 2500 * (i / 10) + 1250;
                    }
                    else{
                        cell[j].location_x = 2500 * (i % 10) + 1350;
                        cell[j].location_y = 2500 * (i / 10) + 1250;                
                    }
                    break; 
                }
            }
                       
        }
    }    
}

void road_build(){//設置道路路口及十字路口座標
    for (int i = 0; i < 121; i++){
        if(i >= 1 && i <= 9){
            road[i].entrance = 1;
            road[i].direction = 0;            
        }
        else if(i >= 111 && i <= 119){
            road[i].entrance = 1;
            road[i].direction = 1;
        }
        else if(i % 11 == 0 && i != 0 && i != 110){
            road[i].entrance = 1;
            road[i].direction = 2;
        }
        else if(i % 11 == 10 && i != 10 && i != 120){
            road[i].entrance = 1;
            road[i].direction = 3;
        }
        else{
            road[i].entrance = 0;
        }

        road[i].location_x =2500 * (i % 11);
        road[i].location_y =2500 * (i / 11);
        //printf("%d %d\n",road[i].location_x,road[i].location_y);
    }
}

int random_entrance(){//5%機率為1(入口進車的機率)
    int flag;
    int x = rand() % 1000 + 1;   

    if(x <= 40){
        flag = 1;
    }
    else{
        flag = 0;
    }

    return flag;
}

int random_direction(){//各方向的機率
    
    int x = rand() % 64 + 1;
    int flag;
    if(x <= 32){
        flag = 0;
    }
    else if(x > 32 && x <= 36){
        flag = 1;
    }
    else if(x > 36 && x <= 50){
        flag = 2;
    }
    else{
        flag = 3;
    }

    return flag;
}

void car_in(){//決定各入口有沒有車進來
    for(int i = 0; i < 121; i++){
        if(road[i].entrance == 1){
            if(random_entrance()){
                 for(int j = 0; j < 2000; j++){
                     if(car[j].exist == 0){
                         car[j].exist = 1;
                         car[j].max_power = 15;
                         //printf("%d\n",car[j].exist);
                         if(road[i].direction == 0){
                             car[j].d_x = 0;
                             car[j].d_y = 1;
                             car[j].location_x = road[i].location_x;
                             car[j].location_y = road[i].location_y;
                         }
                         else if(road[i].direction == 1){
                             car[j].d_x = 0;
                             car[j].d_y = -1;
                             car[j].location_x = road[i].location_x;
                             car[j].location_y = road[i].location_y;                             
                         }
                         else if(road[i].direction == 2){
                             car[j].d_x = 1;
                             car[j].d_y = 0;
                             car[j].location_x = road[i].location_x;
                             car[j].location_y = road[i].location_y;                             
                         }
                         else if(road[i].direction == 3){
                             car[j].d_x = -1;
                             car[j].d_y = 0;
                             car[j].location_x = road[i].location_x;
                             car[j].location_y = road[i].location_y;                             
                         }
                         //printf("%d,%d,%d : %d %d\n",j, car[j].d_x,car[j].d_y,car[j].location_x,car[j].location_y);
                         break;                                                                           
                     }
                 }

            }
        }
    }
    return;
}

void turn(){//到十字路口決定要不要換方向
    for(int j = 0; j < 2000; j++){
        if(car[j].exist == 1){
            if((car[j].location_x % 2500 == 0 && car[j].location_y % 2500 == 0) && car[j].location_x != 0 && car[j].location_y != 0 && 
            car[j].location_x != 25000 && car[j].location_y != 25000){
                if(random_direction() == 1){
                    car[j].d_x = car[j].d_x * -1;
                    car[j].d_y = car[j].d_y * -1;
                }
                else if(random_direction() == 2){
                    if(car[j].d_x == 1){
                        car[j].d_x = 0;
                        car[j].d_y = -1;                        
                    }
                    else if(car[j].d_x == -1){
                        car[j].d_x = 0;
                        car[j].d_y = 1;   
                    }
                    else if(car[j].d_y == 1){
                        car[j].d_x = 1;
                        car[j].d_y = 0;   
                    }
                    else if(car[j].d_y == -1){
                        car[j].d_x = -1;
                        car[j].d_y = 0;   
                    }                                        
                }
                else if(random_direction() == 3){
                    if(car[j].d_x == 1){
                        car[j].d_x = 0;
                        car[j].d_y = 1;                        
                    }
                    else if(car[j].d_x == -1){
                        car[j].d_x = 0;
                        car[j].d_y = -1;   
                    }
                    else if(car[j].d_y == 1){
                        car[j].d_x = -1;
                        car[j].d_y = 0;   
                    }
                    else if(car[j].d_y == -1){
                        car[j].d_x = 1;
                        car[j].d_y = 0;   
                    }                                        
                }                
            }
        }
    }
    return;    
}

void car_go_and_out(){
    for(int j = 0; j < 2000; j++){
        if(car[j].exist == 1){
            car[j].location_x = car[j].location_x + car[j].d_x * 20;
            car[j].location_y = car[j].location_y + car[j].d_y * 20;
            //printf("%d %d\n",car[j].location_x,car[j].location_y);
        }
        if(car[j].location_x < 0 || car[j].location_y <0 || car[j].location_x > 25000 || car[j].location_y > 25000){
            car[j].exist = 0;
            //printf("0\n");
        }
    }
}

int random_call(){//每秒有call的機率
    //int x = rand() % (max - min + 1) + min;
    int flag;
    int x = rand() % 1800 + 1;   

    if(x == 1){
        flag = 1;
    }
    else{
        flag = 0;
    }
    //printf("%d",flag);
    return flag;
}

void call(){
    for(int j = 0; j < 2000; j++){
        if(car[j].exist == 1 && car[j].call == 0){
            if(random_call()){
                car[j].call = 1;
                car[j].call_time =gaussrand();
            }
        }
        if(car[j].exist == 1 && car[j].call == 1){
            car[j].call_time--;
        }
        if(car[j].exist == 1 && car[j].call_time <= 0){
            car[j].call = 0;
        }
    }
}

#define NSUM 25
  
 int gaussrand()
 {
    double x = 0;
    int i;
    for(i = 0; i < NSUM; i++){
        x += (double)rand() / RAND_MAX;
    }
    x -= NSUM / 2.0;
    x /= sqrt(NSUM / 12.0);
    int z = x * 5 + 180;
    return z;
}

double pathloss(int freq, double distance){
    double k_distance = distance / 1000;
    double pathloss = 32.45 + 20 * log10(freq) + 20 * log10(k_distance);
    //printf("%lf\n",pathloss);
    return pathloss;
}
void best(){
    for(int i = 0;i < 2000; i++){        
        if(car[i].call == 1){
            //printf("%d\n",i);
            for(int j = 0;j < 20; j++){
                if(cell[j].exist == 1){
                    distance = sqrt((car[i].location_x - cell[j].location_x) * (car[i].location_x - cell[j].location_x) +
                    (car[i].location_y - cell[j].location_y) * (car[i].location_y - cell[j].location_y));
                    power = 120 - pathloss(cell[j].freq,distance);
                    //printf("%lf\n",power);
                    if(car[i].max_power < power && car[i].cell != j){
                        car[i].cell = j;
                        car[i].max_power = power;
                        check = 1;
                    }

                }
            }
            if(check == 1){
                change_time++;
                check = 0;
                //printf("%d,%d:%d\n",i,car[i].cell,change_time);
            }
        }
    }
    return; 
}

void minium(){
    for(int i = 0;i < 2000; i++){        
        if(car[i].call == 1){
            //printf("%d\n",i);
            for(int j = 0;j < 20; j++){
                if(cell[j].exist == 1){
                    distance = sqrt((car[i].location_x - cell[j].location_x) * (car[i].location_x - cell[j].location_x) +
                    (car[i].location_y - cell[j].location_y) * (car[i].location_y - cell[j].location_y));
                    power = 120 - pathloss(cell[j].freq,distance);
                    //printf("%lf\n",power);
                    if(car[i].max_power < power && car[i].cell != j && car[i].max_power <= 20){
                        car[i].cell = j;
                        car[i].max_power = power;
                        check = 1;
                    }

                }
            }
            if(check == 1){
                change_time++;
                check = 0;
                //printf("%d,%d:%d\n",i,car[i].cell,change_time);
            }
        }
    }
    return;    
}

void entropy(){
    for(int i = 0;i < 2000; i++){        
        if(car[i].call == 1){
            //printf("%d\n",i);
            for(int j = 0;j < 20; j++){
                if(cell[j].exist == 1){
                    distance = sqrt((car[i].location_x - cell[j].location_x) * (car[i].location_x - cell[j].location_x) +
                    (car[i].location_y - cell[j].location_y) * (car[i].location_y - cell[j].location_y));
                    power = 120 - pathloss(cell[j].freq,distance);
                    //printf("%lf\n",power);
                    if((car[i].max_power < power) && (car[i].cell != j) && ((power - car[i].max_power) > 25)){
                        car[i].cell = j;
                        car[i].max_power = power;
                        check = 1;
                    }

                }
            }
            if(check == 1){
                change_time++;
                check = 0;
                //printf("%d,%d:%d\n",i,car[i].cell,change_time);
            }
        }
    }
    return;           
}

void mine(){
    for(int i = 0;i < 2000; i++){        
        if(car[i].call == 1){
            //printf("%d\n",i);
            for(int j = 0;j < 20; j++){
                if(cell[j].exist == 1){
                    distance = sqrt((car[i].location_x - cell[j].location_x) * (car[i].location_x - cell[j].location_x) +
                    (car[i].location_y - cell[j].location_y) * (car[i].location_y - cell[j].location_y));
                    power = 120 - pathloss(cell[j].freq,distance);
                    //printf("%lf\n",power);
                    if((car[i].max_power < power && car[i].cell != j && ((power - car[i].max_power) > 25)) || (car[i].max_power < power && car[i].cell != j && car[i].max_power <= 10)){
                        car[i].cell = j;
                        car[i].max_power = power;
                        check = 1;
                    }

                }
            }
            if(check == 1){
                change_time++;
                check = 0;
                //printf("%d,%d:%d\n",i,car[i].cell,change_time);
            }
        }
    }
    return;    
}