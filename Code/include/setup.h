#ifndef _SETUP_H_
#define _SETUP_H_

#include "basis.h"
#include "parse_arguments.h"
#include "info.h"

void handle_interrupt(int);
void setup_signal_handler();
int setup(int, char**);

void default_algorithm_settings();

void Rail_settings();
void CLR_settings();
void CYC_settings();
void STS_settings();
void ST_Small_settings();
void ST_Medium_settings();
void ST_Large_settings();

void SQL_settings();
void BDBC_settings();
void x264_settings();
void Rail_Small_LLVM_settings();
void BDBJ_settings();
void CYC_Large_settings();

#endif