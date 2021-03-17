/* Jordan Ebel
 * July 2017   
 */

#include "si1145.h" //si1145 sensor header file

static const char *I2C_BUS="/dev/i2c-1";  //is a pointer, meaning the char can’t be modified
static const int I2C_ADDR = 0x60;// address of sensor is fixed

int main(int argv, char **argc)  // Specifies that type of variable the function returns.
     // main() must return an integer
{
    uint16_t vis_data;//unsigned 16 bit integer
    unit16_t ir_data; //Read IR value from the given Si1145 device.
    uint16_t ps1_data;//Read ps value from the given Si1145 device.
    uint16_t ps2_data;
    uint16_t ps3_data;
    uint16_t uv_data;//Read UV index from the given Si1145 device.

    if (si1145_init(I2C_BUS, I2C_ADDR, SI1145_CONFIG_BIT_ALS | // initializes the sensor
                                       SI1145_CONFIG_BIT_UV | 
                                       SI1145_CONFIG_BIT_MEAS_RATE_SLOW |
                                       SI1145_CONFIG_BIT_INDOORS) != SI1145_OK)
    {
        return 1; //program executes successfully
    }

    if (si1145_measurement_auto(SI1145_MEASUREMENT_ALS) != SI1145_OK)
    {
        return 1;
    }

    int i = 0;
 if (si1145_measurement_pause(SI1145_MEASUREMENT_ALS) != SI1145_OK)
    {
        return 1;
    }
        while(1){   //infinite loop
    if (si1145_get_vis_data(&vis_data) != SI1145_OK ||//returns the 16-bit measured data for vis 

        si1145_get_ir_data(&ir_data) != SI1145_OK ||//returns the 16-bit measured data for IR

        //si1145_get_ps_data(&ps1_data, &ps2_data, &ps3_data) != SI1145_OK ||
        si1145_get_uv_data(&uv_data) != SI1145_OK)//returns the 16-bit measured data for UV

    {
        return 1; 
    }
    printf("VIS_DATA: %d\n", vis_data);//prints detected value
    printf("IR_DATA: %d\n", ir_data);//prints detected value
 //printf("PS1_DATA: %d\n", ps1_data);
    ///printf("PS2_DATA: %d\n", ps2_data);
    //printf("PS3_DATA: %d\n", ps3_data);
    printf("UV_DATA: %f\n", ((float)uv_data/(float)65536)*10);////prints detected value

        sleep(1); //make the program wait  for  1s
}    
si1145_close();//closes a file descriptor

    return 0; //program executes successfully
}



