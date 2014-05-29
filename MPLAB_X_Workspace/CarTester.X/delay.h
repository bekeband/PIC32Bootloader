/* 
 * File:   delay.h
 * Author: Tulajdonos
 *
 * Created on 2014. május 29., 10:20
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif

    void InitCoreTimer();
    void DelayMs(int msec);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

