#include "eeprom.h"


Eeprom::Eeprom()
{
    
}


unsigned int Eeprom::eeprom_countor_read(void)
{
    unsigned int eeproma,eepromshuil;
    
    for(eeproma=0;eeproma<9;eeproma++)
    {
        if(EEPROM_VALUE_SHUILIANGDECIMAL(eeproma)!=EEPROM_MARK_SHUILDECIMAL)      
            break;
    }
    
    eepromshuil=EEPROM_VALUE_SHUILIANGMAIN;
    eepromshuil+=eeproma;
    
    return (unsigned short)eepromshuil;
}


unsigned int Eeprom::eeprom_countor_write(unsigned int watervalue)
{
    unsigned int eepromb;
    
    /*
    /FLASH_ErasePage(EEPROM_ADDR_PAGE0);
    FLASH_ErasePage(EEPROM_ADDR_PAGE1); 
    FLASH_ErasePage(EEPROM_ADDR_SHUILIANGMAIN);
    
    HAL_FLASH_Program(1, EEPROM_ADDR_SHUILIANGMAIN, eepromshuil);
    */
        
    return eepromb;
}

unsigned int Eeprom::eeprom_countor_addone(void)
{
    unsigned int eepromb,eeproma,eepromshuil;
    
    __disable_irq();
    
    eepromb=HAL_FLASH_Unlock();
    
    for(eeproma=0;eeproma<10;eeproma++)
    {
        if(EEPROM_VALUE_SHUILIANGDECIMAL(eeproma)!=EEPROM_MARK_SHUILDECIMAL)      
            break;  

    }
    //pc.printf("eeproma=%d\n",eeproma);
       
    if(eeproma>8)
    {
        eepromshuil=EEPROM_VALUE_SHUILIANGMAIN;
        eepromshuil+=10;
             
        for(eepromb=0;eepromb<9;eepromb++)
        {
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EEPROM_ADDR_PAGE1+4*eepromb, 0);
            wait(0.02);
        }
        
        eepromb=HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EEPROM_ADDR_SHUILIANGMAIN, 0);
        wait(0.02);
        eepromb=HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EEPROM_ADDR_SHUILIANGMAIN, eepromshuil);
        wait(0.02);
    }
    else
    {
        eepromb=HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EEPROM_ADDR_SHUILIANGDECIMAL+eeproma*4, EEPROM_MARK_SHUILDECIMAL);    
        wait(0.02);
    }
                
    eepromb=HAL_FLASH_Lock();
    
    __enable_irq();
    
    return eepromb;
}