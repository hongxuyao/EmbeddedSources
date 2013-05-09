#include "keyif.h"

// 读取按键物理状态的函数。
u8_t KeyRead(u8_t kindex)
{
    switch(kindex){
    case 0:     // 按键#0
        if(PIN_DOWN(0)){
            return 1;
        }
        return 0;
    case 1:     // 按键#1
        if(PIN_DOWN(1)){
            return 1;
        }
        return 0;
    case 2:     // 按键#2
        if(PIN_DOWN(2)){
            return 1;
        }
        return 0;
    case 3:     // 按键#3
        if(PIN_DOWN(3)){
            return 1;
        }
        return 0;
    }
    return 0;
}

// 按键事件处理函数。
u8_t KeyProc(u8_t kindex, u8_t ksta, u8_t ktick)
{
    switch(kindex){
    case 0:     // 按键#0
        if(ksta == KEY_STA_BEGIN){
            // 按键被按下，TODO SOMETHING。
            
            return 0;
        }
        else if(ksta == KEY_STA_KEEP){
            // 按键被保持，TODO SOMETHING。
            
            return 0;
        }
        else if(ksta == KEY_STA_END){
            // 按键被松开，TODO SOMETHING。
            
            return 0;
        }
        break;
    case 1:     // 按键#1
        if(ksta == KEY_STA_KEEP && ktick == 1000/KEY_PERIOD_MS){
            // 按键按下保持了1000毫秒，TODO SOMETHING。
            
            return 1;
        }
        break;
    case 2:     // 按键#2
        if(ksta == KEY_STA_KEEP && ktick == 1){
            // 按键被按下，具备了间隔KEY_PERIOD_MS毫秒的去抖动时间，TODO SOMETHING。
            
            return 1;
        }
        break;
    case 3:     // 按键#3
        if(ksta == KEY_STA_END){
            // 响应按键松开事件，TODO SOMETHING。
            
        }
        break;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| 函数名称 |: main
//| 功能描述 |: 
//|          |: 
//| 参数列表 |: 
//|          |: 
//| 返    回 |: 
//|          |: 
//| 备注信息 |: 
//|          |: 
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    // 初始化KEYIF。
    kif_Init();
    
    while(1){
        delay(KEY_PERIOD_MS);
        // 以KEY_PERIOD_MS毫秒为周期调用。
        kif_TickHook();
    }
}
