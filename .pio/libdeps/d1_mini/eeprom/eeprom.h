/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "mbed.h"







#ifndef SANFAN_EEPROM_H
#define SANFAN_EEPROM_H

#include "platform.h"



//eeprom storage
#define EEPROM_ADDR_PAGE0 0X08080000
#define EEPROM_ADDR_PAGE1 0X08080080
#define EEPROM_ADDR_PAGE2 0X08080100
#define EEPROM_ADDR_PAGE3 0X08080180
#define EEPROM_ADDR_PAGE4 0X08080200
#define EEPROM_ADDR_PAGE5 0X08080280
#define EEPROM_ADDR_PAGE6 0X08080300
#define EEPROM_ADDR_PAGE7 0X08080380
#define EEPROM_ADDR_PAGE8 0X08080400
#define EEPROM_ADDR_PAGE9 0X08080480
#define EEPROM_ADDR_PAGE10 0X08080500
#define EEPROM_ADDR_PAGE11 0X08080580
#define EEPROM_ADDR_PAGE12 0X08080600
#define EEPROM_ADDR_PAGE13 0X08080680
#define EEPROM_ADDR_PAGE14 0X08080700
#define EEPROM_ADDR_PAGE15 0X08080780

#define EEPROM_ADDR_BIAOHAO                 EEPROM_ADDR_PAGE10
#define EEPROM_ADDR_SHUILIANGDECIMAL        EEPROM_ADDR_PAGE1
#define EEPROM_ADDR_SHUILIANGMAIN           EEPROM_ADDR_PAGE15
#define EEPROM_ADDR_SHUILIANGBACKUP         EEPROM_ADDR_PAGE14
#define EEPROM_ADDR_UPFREQ                  100

#define EEPROM_VALUE_BIAOHAO                *(unsigned int *)EEPROM_ADDR_BIAOHAO
#define EEPROM_VALUE_SHUILIANGDECIMAL(n)    *((unsigned int *)(EEPROM_ADDR_PAGE1+n*4))
#define EEPROM_VALUE_SHUILIANGMAIN          *(unsigned int *)EEPROM_ADDR_SHUILIANGMAIN
#define EEPROM_VALUE_SHUILIANGBACKUP        *(unsigned int *)EEPROM_ADDR_SHUILIANGBACKUP

#define EEPROM_MARK_SHUILDECIMAL         0X55




class Eeprom {

public:
    Eeprom();

    unsigned int eeprom_countor_read();
    unsigned int eeprom_countor_write(unsigned int watervalue);
    unsigned int eeprom_countor_addone();
    
    
    unsigned short open(void);
    unsigned short close(void);
    
/*
private:

   
    */
protected:
  
};

#endif



