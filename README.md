# class `IC74HC595` 

ADT representing an IC74H595-based parallel output buffer.

The [IC74HC595](#classIC74HC595) IC is an 8-channel serial-in-parallel-out (SIPO) buffer. Multiple IC74H595's can be daisy-chained to increase the number of available output channels in increments of eight.

In this abstraction the state of all buffer output channels is represented by an integer 'status' value which on architectures with 32-bit integers limits the maximum number of daisy-chained buffers that can be operated to four.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`IC74HC595`](#classIC74HC595_1a708326f72afe13f1d4c53c078aa9890b)`(unsigned char gpioClock,unsigned char gpioData,unsigned char gpioLatch,unsigned int buffer)` | Construct a new buffer.
`public void `[`begin`](#classIC74HC595_1a66416a0c85080cd00c3ebede9fca3f7b)`()` | Initiliase buffer.
`public void `[`write`](#classIC74HC595_1a089c9670aa7294bd942fc5439124ef01)`(unsigned int status,unsigned int mask)` | Set buffer output channel states.
`public void `[`configureCallback`](#classIC74HC595_1ae79db8eb5438aba43f9c9317bda1a607)`(unsigned int(*)(unsigned int buffer) callback,unsigned long updateInterval)` | Configure regular buffer updates.
`public void `[`callbackMaybe`](#classIC74HC595_1a9b94635c84aedde3e0df7452a0139763)`(bool force)` | Perform regular or ad-hoc buffer updates.

## Members

#### `public  `[`IC74HC595`](#classIC74HC595_1a708326f72afe13f1d4c53c078aa9890b)`(unsigned char gpioClock,unsigned char gpioData,unsigned char gpioLatch,unsigned int buffer)` 

Construct a new buffer.

#### Parameters
* `gpioClock` - GPIO pin connected to the IC74H595 clock pin. 

* `gpioData` - GPIO pin connected to the IC74H595 data pin. 

* `gpioLatch` - GPIO pin connected to the IC74H595 data pin. 

* `buffer` - number of IC74H595 ICs in the buffer daisy-chain (optional: defaults to 1).

#### `public void `[`begin`](#classIC74HC595_1a66416a0c85080cd00c3ebede9fca3f7b)`()` 

Initiliase buffer.

This method must be called from setup() before any attempt is made to write data to the buffer. GPIO pin modes are set to OUT and all buffer output channels status set to OFF.

#### `public void `[`write`](#classIC74HC595_1a089c9670aa7294bd942fc5439124ef01)`(unsigned int status,unsigned int mask)` 

Set buffer output channel states.

Each bit in *status* defines the output state of a single parallel output channel: bits 0 through 7 define the states of channels 0 through 7 on the first buffer IC in any daisy chain; bits 8 through 15 the states of channels 0 throgh 7 on any second buffer IC and so on.

The *mask* value can be used to restrict updates to just those channels selected by a 1 bit in the *mask* value.

#### Parameters
* `status` - the value to be written to the buffer. 

* `mask` - buffer channels to be updated (optional: default is 0xffffffff which says all channels).

#### `public void `[`configureCallback`](#classIC74HC595_1ae79db8eb5438aba43f9c9317bda1a607)`(unsigned int(*)(unsigned int buffer) callback,unsigned long updateInterval)` 

Configure regular buffer updates.

This method schedules the callback of a function in the host application which will be used to regularly update the status of the buffer.

The specified callback function is passed the current buffer status as its only argument and must return a new status value which will be promptly written to the buffer.

Typically this method should be called from setup().

#### Parameters
* `callback` - a callback function. 

* `updateInterval` - interval between invocations of *callback* in milliseconds (optional: defaults to 1s).

#### `public void `[`callbackMaybe`](#classIC74HC595_1a9b94635c84aedde3e0df7452a0139763)`(bool force)` 

Perform regular or ad-hoc buffer updates.

This method should typically be called from loop() with to trigger an invocation of any configured callback function at the configured update interval. The method can be call with *force* set to true to invoke an immediate callback.

The [configureCallback()](#classIC74HC595_1ae79db8eb5438aba43f9c9317bda1a607) method must be used to set up callback parameters before this method is executed.

#### Parameters
* `force` - if true, forces an immediate invocation of any configured callback (optional: default to false).

Generated by [Moxygen](https://sourcey.com/moxygen)