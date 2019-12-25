
## Smart-D-LED-API

[DEMO - API with android application](https://www.youtube.com/watch?v=K5LZp9m322Y)

## Related projects

#### [ Smart D-LED-API](https://github.com/DylanMeng/Smart-D-LED-API)

#### [ Smart D-LED-REMOTE](https://github.com/DylanMeng/Smart-D-LED-REMOTE)

#### [ Smart D-LED-PCB](https://github.com/DylanMeng/Smart-D-LED-PCB)

#### [ Smart D-LED-TOOLS](https://github.com/DylanMeng/Smart-D-LED-TOOLS)

#### [ Smart D-LED-TOWER](https://github.com/DylanMeng/Smart-D-LED-Tower)
##

Software, hardware and product development can be time consuming and expensive. If you appreciate the development of Smart-D-LED or any of my projects please consider donating.

Your donation will help me continue the development and support of Smart-D-LED.

[![Donate](https://img.shields.io/badge/Donate-PayPal-blue.svg)](https://www.paypal.me/DMeng)

## Setup

- Now using forked external library, to be able to compile please use visual studio with vmicro.

## Contribution

If you want to add a cool pattern or effect in Smart-D-LED-API, please consider this: 
- Patterns: 
	- No delay allowed only millis()
	- Try not to have multiple dled.refresh() (already in loop())
	- See Patterns/confetti.h for an example 

- Effects: 
	- Consider an effect as an overlay 
	- (effect overrides pattern data) 
	- No delay allowed only millis() 
	- Try not to have multiple dled.refresh() (already in loop())
	- See Effects/vumeter.h for an example

## Features
- More information coming soon!

## Relase History

- 0.0.2 (TO-DO)
	- Fix OTA update via SPI flash
	- Fix Smart-D-LED bonjour
	- Add ON/OFF + fade for brightness control
- 0.0.1
	- Inital release 

