/*
 * Copyright 2010 by Adam Mayer	 <adam@makerbot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "StepperInterface.hh"

void StepperInterface::setDirection(bool forward) {
	dir_pin.setValue(forward);
}

void StepperInterface::step(bool value) {
	step_pin.setValue(value);
}

void StepperInterface::setEnabled(bool enabled) {
	// The A3982 stepper driver chip has an inverted enable.
	enable_pin.setValue(!enabled);
}

bool StepperInterface::isAtMaximum() {
	bool v = max_pin.getValue();
	if (invert_endstops) v = !v;
	return v;
}

bool StepperInterface::isAtMinimum() {
	bool v = min_pin.getValue();
	if (invert_endstops) v = !v;
	return v;
}

void StepperInterface::init() {
	dir_pin.setDirection(true);
	step_pin.setDirection(true);
	enable_pin.setValue(true);
	enable_pin.setDirection(true);
	max_pin.setDirection(false);
	min_pin.setDirection(false);
	// pull pins up to avoid triggering when using inverted endstops
	max_pin.setValue(invert_endstops);
	min_pin.setValue(invert_endstops);
}