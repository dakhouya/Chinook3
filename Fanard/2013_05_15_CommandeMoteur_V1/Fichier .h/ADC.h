#include "p33EP512MC806.h"
#include "Global.h"

#define NB_BUFF 16
#define NB_ANALYSE 50
#define NB_CAR_AFF 20

#define ADC_VOLTAGE 3.3f
#define G_ADC 1024.0f


void init_ADC();

void Analyse_ADC(float *BUFF,float OFFSET[16],int BUFF_val[16]);