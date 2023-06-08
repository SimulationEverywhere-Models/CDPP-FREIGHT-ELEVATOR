/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Marcelo Gutierrez Alcaraz
*
*  EMAIL: marcelo@sce.carleton.ca
*
*  DATE: October 19, 2005
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
//#include "buffer.h"      // class Buffer
#include "Econtrol.h"   //class Econtrol



void MainSimulator::registerNewAtomics()
{
//	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Evehicle>() , "Evehicle" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Econtrol>() , "Econtrol" ) ;
//	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Ecall>() , "Ecall" ) ;
}
