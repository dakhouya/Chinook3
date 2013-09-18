/* 
 * File:   Global.h
 * Author: Utilisateur-pc
 *
 * Created on 26 avril 2013, 22:11
 */

#ifndef GLOBAL_H
#define	GLOBAL_H
    
#ifdef	__cplusplus
extern "C" {
#endif

#define PWMA    PWMCON2
#define PWMB    PWMCON4
#define PWMC    PWMCON6
#define PWMD    PWMCON1
#define PWME    PWMCON3
#define PWMF    PWMCON5


#define FOSCP  100.0f
#define MAX_TRAVEL 5600     //14tours X 400 demi-pas


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

