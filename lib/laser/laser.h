#pragma once
#include <inc.h>
#include <firebaseInit.h>

// Creating a wrapper for laser
// so that the call for the 
// functions are clearer
namespace laser
{
	bool isHit();

	// Shoot the laser from the robot
	void emit();

	// Stop shooting laser from robot
	void stopEmitting();

	// Initialize the lasers
	void init();
};