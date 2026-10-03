# MicroPython for Raspberry Pi Pico: save as main.py. Same protocol as the Arduino sketch.
import sys, time
from machine import Pin
green, red, buzz = Pin(15, Pin.OUT), Pin(14, Pin.OUT), Pin(13, Pin.OUT)
def beep(n, on, off):
    for _ in range(n):
        buzz.on(); time.sleep_ms(on); buzz.off(); time.sleep_ms(off)
while True:
    c = sys.stdin.read(1)
    green.off(); red.off()
    if c == 'G':
        green.on(); time.sleep_ms(1500); green.off()
    elif c == 'R':
        red.on(); time.sleep_ms(1500); red.off()
    elif c == 'E':
        beep(3, 120, 120)
    sys.stdout.write('A')
