/*******************************************************************
*
*  DESCRIPTION: class Ecall - Call Generation for a Freight Elevator
*
*  AUTHOR:  Marcelo Gutierrez Alcaraz
*
*  EMAIL: marcelo@sce.carleton.ca
*
*  DATE: October 19, 2005
*
*******************************************************************/

#ifndef __ECALL_H
#define __ECALL_H

/** include files **/
#include "atomic.h"     // class Atomic


/** declarations **/
class Ecall : public Atomic
{
public:
	Ecall( const string &name = "Ecall" );	// Default constructor

	~Ecall();

	virtual string className() const
		{return "Ecall";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	int     des_maker;
	int		acall_gen;
	const	Port	&inside_call;
	const	Port	&outside_call;
	Port    &call_gen;

			
};	// class ecall


#endif   //__ECALL_H 
