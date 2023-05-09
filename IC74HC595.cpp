/**********************************************************************
 * IC74HC595.cpp - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include <Arduino.h>
#include "IC74HC595.h"

IC74HC595::IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
  this->staus = 0;
}

void IC74HC595::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, OUTPUT);
  pinMode(this->gpioLatch, OUTPUT);
  this->write(this->status);
}

void IC74HC595::write(unsigned int status, unsigned int buffers) {
  this->status = status;
  digitalWrite(this->gpioLatch, 0);
  for (unsigned int i = buffer; i > 0; i--) {
    shiftOut(this->gpioData, this->gpioClock, MSBFIRST, (this->status >> ((i - 1) * 8)) & 0xff);
  }
  digitalWrite(this->gpioLatch, 1);
}

void IC74HC595::writeBit(unsigned int state, unsigned int bit) {
  if (state) {
    this->status |= (1UL << bit);
  } else {
    this->status &= ~(1UL << bit);
  }
  this->write(this->status, (bit / 8) + 1);
}

void IC74HC595::configureCallback(unsigned int (*callback)(unsigned int buffer), unsigned long callbackInterval, unsigned int buffers) {
  this->callback = callback;
  this->callbackInterval = callbackInterval;
  this->callbackBuffers = buffers;
}

void IC74HC595::callbackMaybe(bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || force) {
    this->write(this->callback(this->buffer), this->callbackBuffers);
    deadline = (now + this->callbackInterval);
  }

}
