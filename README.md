# UART
ATmega128 AVR Microprocessor는 53개의 GPIO Pin으로 n Bit의 데이터를 전송하기 위해, n 개의 IO Pin을 사용하는   
병렬(Parallel) 통신이 가능하다. 하지만 Pin이 많아지면 회로가 많아지므로 고속 데이터 처리만 사용한다.

-----

# 시리얼 통신 (직렬통신, Serial Communication)
![](http://dl.dropbox.com/s/08owzzxpisuyedh/Serial0.jpg)  
사전을 찾아보면 Serial은 순차적인, 연속되는 등의 뭔가의 일을 계속 반복한다는 의미이다.

**Serial Communication은 1 Byte 데이터를 한 번의 통신으로 1 Bit 씩, 순차적으로 Transmit / Receive 하는 통신.**  
![](https://dl.dropbox.com/s/nguekvkfkfpsfue/SerialFrame.png)

모든 Byte를 한 번으로 동시 전달하는 병렬 통신과 달리 Serial 통신은 속도가 느리지만 간단하며 장거리도 지원한다.  
Parallel 통신 용 IEEE 488 스펙을 보면 기기간 케이블링은 총 20m 미만이어야 하며, 두 개의 디바이스 간은 2m 미만.  
반면 Serial 통신은 최대 1.2Km의 통신거리를 보장한다.

-----

# UART (Universal Asynchronous Receiver Transmitter)
GPS modules, LCD displays, and XBee radios와 같은 복잡한 주변 디바이스는 일반적으로   
Universal Asynchronous Receiver Transmitter (UART) 포트로 통신한다. 흔히 Serial 포트 라고도 한다.

## UART는 Raw Data를 주변 디바이스와 교환하기 위한 범용 인터페이스.
데이터 전송 속도와 데이터 Byte 형식 모두 구성 가능하기 때문에 범용적이다.

1. **두 디바이스 간의 데이터 전송을 동기화 클록 신호가 없는 비동기식 (Asynchronous) 통신.**  
   I²C, SPI 통신은 동기화 클럭 신호에 맞춰서 데이터가 전송되는 동기식 (Synchronous) 통신.

2. 디바이스 하드웨어는 FIFO (입출력 버퍼)에 들어오는 모든 데이터를 어플리케이션에서 읽을 때까지 수집.  
   **UART 데이터 전송은 전이중 방식(Full-Duflex)이므로 입출력 데이터를 동시에 주고받을 수 있다.**   

I²C 보다 빠르지만 공유 클럭이 없으므로, 두 디바이스가 최소한의 타이밍 오류로 독립적으로 고수 할 수 있는     
공통 데이터 전송 속도에 동의해야 한다. 또한, SPI, I²C와 달리 UART 두 디바이스 간 point-to-point 통신만 지원한다.  
(다수의 디바이스 간 병렬 연결 x)


> **Raw Data**  
> Primary Data라고도 하는 Raw Data는 소스에서 수집 한 조작하지 않은 데이터이다. (숫자, 계기 판독 값, 수치 등)  
> **``Raw Data``는 컴퓨터처럼 전자 디바이스의 ``Binary Data``. (``2진 데이터``, ``low-level data``)**

-----

## RS232
**RS232는 IBM 호환 PC에서 쓰이는 Serial Interface.**

컴퓨터를 주변 디바이스에 연결하거나 계측기 컨트롤 등 여러 용도로 RS232를 사용한다. RS232 하드웨어는  
최장 15 m (50 ft)까지 통신 가능하며, PC Serial 포트와 디바이스 간 point-to-point 통신 만 지원한다.

## RS422
**RS422는 Apple 사의 Mac에서 사용되는 Serial Interface.**

RS232가 접지 참조된 불균형 (Unbalanced) 신호를 채택하고 있는 것과 달리 RS422는 차동 전기 신호를 사용한다.   
차동 전송 방법은 신호 송수신시 2개의 라인을 각각 사용하며 따라서 RS232에 비해 노이즈가 적고 장거리 통신 보장.  
(노이즈 제거 및 확장된 통신 거리는 산업 어플리케이션에 있어 중요한 요소.)

## RS485
**Multidrop 기능으로 단일 RS485 Serial 포트에 연결된 디바이스의 네트워크를 생성하는 Serial Interface.**

PC 네트워크로 연결된 여러 분산 디바이스가 필요하거나 데이터 수집, HMI 또는 기타 작업 컨트롤러를 필요로 하는   
산업용 어플리케이션에 있어 노이즈 제거 및 Multidrop 기능을 갖춘 RS485는 최상의 선택이다.   

RS485는 RS422의 상위 집합이므로 모든 RS422 디바이스는 RS485에 의해 컨트롤 할 수 있고,    
RS485 하드웨어를 사용하면 최장 1.2Km (4000 ft) 케이블 시리얼 통신을 수행할 수 있다.

> **Multidrop**  
> 하나의 송신 디바이스로 여러개의 수신장치가 연결되는 Parallel Bus 구조.

-----

# UART Interface
![](http://dl.dropbox.com/s/xbp4kz7em0lkr5r/uart-connections.png)

* **3-Wire ports include data receive (RX), data transmit (TX), and ground reference (GND) signals.**
* 5-Wire ports add **Request To Send** and **Clear To Send** signals used for **hardware flow control.**  
  Flow control allows the receiving device to indicate that its FIFO buffer is temporarily full and  
  the transmitting device should wait before sending any more data.

> **Rx, Tx 라인은 반드시 교차 연결.**  

# Hardware Flow Control (Handshaking)
![](http://dl.dropbox.com/s/qo716i03ab6cv5v/uart-flow-control.png)

디바이스가 5-wire UART 포트를 지원하는 경우 Hardware Flow Control로 데이터 전송의 신뢰성을 높일 수 있다.  
이는 또한 자주 들어오는 데이터가 누락 될 가능성이 있는 고속 baud rate를 안전하게 사용할 수 있음을 의미한다.

## RTS (Request to Send) & CTS (Clear to Send)
리시버에서 데이터를 받을 준비가 되면 RTS 신호를 활성화하여 데이터 수신 준비가 되었음을 알린다.  
트랜시버에서는 이 신호를 CTS 입력을 통해 인식하고, 데이터를 전송이 준비되었으므로 데이터를 보내달라는 뜻이다.

UART는 수신 버퍼가 가득 차서 더 이상 데이터를 수신 할 수 없을 때 RTS 신호를 활성. 버퍼가 고갈되면 신호가 제거.  
마찬가지로, UART는 CTS 신호를 모니터링하고 주변 장치에 의한 신호를 보게되면 데이터 전송을 일시 중지한다.

## DTR (Data Terminal Ready) & DSR (Data Set Ready)
디바이스 간 서로의 상태 파악을 위한 신호. 디바이스 터미널이 준비되면 DTR 라인이 활성화되어 알린다.   
DSR 라인에서 DTR 신호를 인지하고 데이터를 보낼 수 있다.  

일반적으로 디바이스 간 DTR / DSR 라인을 사용하여 시스템이 통신할 준비가 되었음을 알리고,   
RTS / CTS 라인은 단위별 데이터 패킷을 대상으로 사용한다.

![](http://dl.dropbox.com/s/c1uc409pkcfwv9p/SerialInterface.png)

-----

# Baud Rate
## UART를 통한 데이터의 초당 Bit 전송 속도.

UART로 연결된 두 디바이스 간 공유 클럭이 없으므로, 데이터를 올바르게 디코딩하기 위한 동일한 Baud Rate를  
구성하고 일치시켜야 한다. 프로토콜에 4800 Baud Rate라고 나오는 경우 클럭이 4800 Hz로 작동한다는 뜻이다.  
(Serial 포트는 4800 Hz로 데이터 라인을 샘플링, 초 당 4800 Bit 전송)

일반적인 Baud Rate는 ``9600``, ``19200``, ``38400``, ``57600``, ``115200`` 및 ``921600`` bps.  
데이터 프레임의 Over Head (Start Bit, Stop 및 Parity Bit)가 포함되므로 유효 데이터 전송 속도는 약간 낮아지고,   
구성한 프레임 Bit 수에 따라 달라진다. 단, 보다 높은 속도도 가능하지만 디바이스를 분리할 수 있는 거리가 줄어든다.

-----

# The Data Frame
UART를 통해 전송 된 모든 문자는 다음 구성 요소가 포함 된 **데이터 프레임** 으로 래핑.  
![](http://dl.dropbox.com/s/fyzcuql2w6e2byu/uart-frame.png)

## Start Bit
데이터를 보내기 전, Start Bit는 새로운 문자의 시작을 나타내기 위해 1 Bit 지속 시간의 고정 된 시간 간격 동안  
활성 상태로 유지. Start Bit는 리시버가 Data Bit를 동기화 하도록 하고, 리시버가 각각의 Bit의 중간점을 샘플링  
하기 위한 자신만의 클럭을 생성할 수 있는게 해준다.

## Data Bit
데이터 문자를 나타내는 개별 Bit.  

* UART는 문자를 나타 내기 위해 5-9 Data Bit를 전송하도록 구성.  
* Bit 수가 적 으면 데이터 범위는 줄어들지 만 유효 데이터 전송 속도는 증가.  
* 표준 ASCII는 0 ~127 (7 Bit), 확장된 ASCII는 0 ~ 255 (8 Bit)  
* 전송하려는 데이터가 단순 Text (표준 ASCII) 경우, 패킷당 7 Bit의 데이터를 보내면 통신 ok.

> **패킷 (Packet)**  
> 패킷은 단일 바이트 전송을 의미하며, Start, Stop Bit, Data Bit, Parity Bit가 포함.   
> 실제 Bit의 수는 선택된 프로토콜에 따라 달라지므로 모든 경우를 포괄하는 "패킷"이라는 용어를 사용.

## Parity Bit
선택적 오류 검사 값.

UART가 Even 또는 Odd Parity로 구성되면 여분의 Bit가 프레임에 추가되어 Data Bit의 내용이  
Even 또는 Odd 값의 합계인지 여부를 검사한다. none으로 설정하면 프레임에서 Bit가 제거.

## Stop Bit
모든 데이터가 단일 패킷에 대한 통신의 종료 알림 및 전송된 후 해당 문자의 끝을 표시하기 위해 구성 가능한  
시간 간격 동안 통신 라인이 재 설정. 1 또는 2 Bit 지속 기간 동안 유휴 상태로 유지되도록 구성 할 수 있다.

데이터는 모든 라인을 통해 클럭되며, 각 디바이스는 고유의 클럭이 있기 때문에 서로의 디바이스가 동기화가 되지  
않을 가능성이 있다. 따라서 정지 Bit는 전송의 종료 알림과 클럭 속도 오류를 방지하기 위한 완충 역할도 한다.  

단, 많은 Bit가 Stop Bit에 쓰이면 다른 클럭을 동기화할 수 있지만 데이터 전송 속도는 느려진다.

-----

## UART 디바이스 기본 구성은 8 Data Bit, No Parity 및 1 Stop Bit (8N1) 총 10 Bit.
송신 측에서 데이터를 보내지 않으면 데이터 핀은 항상 ``1``, 데이터가 수신되기 시작하는 시점에서  
데이터 핀은 ``0``으로 설정되고, 이어서 8 Bit의 Data가 수신된 후 데이터 전송이 종료됨을 알리는 ``1`` 수신.

![](http://dl.dropbox.com/s/83zxfa0lbftel3m/UartTimeChart.png)

-----

# MAX232 Serial Level Converter
![](http://dl.dropbox.com/s/yscsjoaoitaz83b/MAX232.jpg)

**MAX232는 다수의 Microprocessor와 Serial 통신할 때 Signal Level을 3.3v 혹은 5v TTL Level로 변환하는 IC.**  
RS-232 (v.23) Serial 통신은 -15v ~ 15v 사이에서 동작한다. 하지만 TTL 로직은 0v ~ 5v 사이에서 동작한다.  
최근의 저전력 로직은 0v ~ 3.3V 사이에서 동작하기도 하며 더 낮은 전압으로도 동작한다.
 
RS-232 Signal Level은 TTL 보다 너무 높은 전압이고, RS-232의 -15v는 일반적인 Microprocessor로 처리할 수 없다.  
RS-232 Interface로부터 데이터를 받기 위해서는 전압을 다운시키고, Low와 High Level 전압은 반전시켜야 한다.

![](http://dl.dropbox.com/s/k5zhax4y8l3ax4u/MAX232_Circuit.png)

> **Datasheet**   
> http://pdfserv.maximintegrated.com/en/ds/MAX220-MAX249.pdf

-----

[Android Things UART](https://developer.android.com/things/sdk/pio/uart.html)  
[NI UART](http://www.ni.com/white-paper/2895/ko/#toc2)  
[CocoaFab](https://kocoafab.cc/tutorial/view/596)
