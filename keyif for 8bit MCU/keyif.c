#include "keyif.h"
#include <string.h>

#if defined(KEY_NUM_MAX) && (KEY_NUM_MAX > 0)

#if KEY_NUM_MAX > 255
#error 该模块为8位单片机优化，不支持255个以上按键。
#endif

static u8_t kticks[KEY_NUM_MAX];            // 每个按键需要1字节计时器。
static u8_t kstats[(KEY_NUM_MAX+7)/8];      // 每个按键需要1BIT的状态标志。
static u8_t kvalid[(KEY_NUM_MAX+7)/8];      // 每个按键需要1BIT的有效标志。
////////////////////////////////////////////////////////////////////////////////
//|          |
//| 函数名称 |: kif_Init
//| 功能描述 |: 
//|          |: 
//| 参数列表 |: 
//|          |: 
//| 返    回 |: 
//|          |: 
//| 备注信息 |: 
//|          |: 
////////////////////////////////////////////////////////////////////////////////
void kif_Init(void)
{
    memset(kticks, 0, sizeof(kticks));
    memset(kstats, 0, sizeof(kstats));
    memset(kvalid, 0, sizeof(kvalid));
}

////////////////////////////////////////////////////////////////////////////////
//|          |
//| 函数名称 |: kif_TickHook
//| 功能描述 |: 
//|          |: 
//| 参数列表 |: 
//|          |: 
//| 返    回 |: 
//|          |: 
//| 备注信息 |: 
//|          |: 
////////////////////////////////////////////////////////////////////////////////
void kif_TickHook(void)
{
    u8_t now, msk;
    u8_t i, grp;
    
    grp = 0;
    msk = 1;
    for(i = 0; i < KEY_NUM_MAX; ++i){
        now = (KeyRead(i) ? msk : 0);
        if((kstats[grp] ^ now) & msk){
            // 按键状态发生变化。
            kstats[grp] ^= msk;
            if(now){
                // 按键刚被按下。
                kticks[i] = 0;
                kvalid[grp] |= msk;
                if(KeyProc(i, KEY_STA_BEGIN, 0)){
                    kvalid[grp] &= ~msk;
                }
            }
            else{
                // 按键刚被抬起。
                kticks[i] += 1;
                KeyProc(i, KEY_STA_END, kticks[i]);
            }
        }
        else if(now){
            // 按键保持按下状态。
            kticks[i] += 1;
            if(kvalid[grp] & msk){
                // 按键处于有效状态。
                if(KeyProc(i, KEY_STA_KEEP, kticks[i])){
                    kvalid[grp] &= ~msk;
                }
            }
        }
        // 处理用于加速执行的中间变量。
        msk <<= 1;
        if(msk == 0){
            msk = 1;
            grp++;
        }
    }
}

#else /* KEY_NUM_MAX */

void kif_Init(void){ ; }
void kif_TickHook(void){ ; }

#endif /* KEY_NUM_MAX */

