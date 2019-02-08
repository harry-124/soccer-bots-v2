import XBee_Threaded
from time import sleep
print 'Enter port  number /dev/ttyACM'
st="/dev/ttyACM"
port = raw_input()
xbee = XBee_Threaded.XBee(st+port)
print "connected"
import pygame

if __name__ == "__main__":
    pygame.init()
    done = False

    r = 50.760/1000 # metres-wheel radius
    R = 150.000/1000 # metres-bot radius
    wz = 0.5 #rps-wheel

    clock = pygame.time.Clock()

    pygame.joystick.init()
    
    while True:
        try:
            for event in pygame.event.get(): 
                if event.type == pygame.QUIT: 
                    done=True 

            joystick_count = pygame.joystick.get_count()


            for i in range(joystick_count):
                joystick = pygame.joystick.Joystick(i)
                joystick.init()
                name = joystick.get_name()
        
                axes = joystick.get_numaxes()
        
                vx = joystick.get_axis(3)
                vx = vx*abs(vx)
                vy = joystick.get_axis(4)
                vy = vy*abs(vy)
                ds = joystick.get_axis(5)

                buttons = joystick.get_numbuttons()

                k = joystick.get_button(0) ## 0 or 1 -> kick
                LB = joystick.get_button(4) ## 0 or 1 -> anti-clockwise rotation
                RB = joystick.get_button(5) ## 0 or 1 -> clockwise rotation

                if(LB == 0 and RB ==1):
                    wz = -0.1
            if(LB == 1 and RB ==0):
                wz = 0.1
            if( ( LB ==0 and RB == 0 ) or ( LB==1 and RB == 1 ) ):
                wz = 0

            vx = vx*0.06 ## value from -0.2 to 0.2
            vy = -vy*0.06 ## value from -0.2 to 0.2    

            if ds < 0:
                ds = 0 ## value from 0 to 1
            ds = int(ds*255)
        
            w1 = ((vx/1.732)/r) - ((vy/3)/r) + ((wz*R)/r)
            w2 = ((vy/1.5)/r) + ((R*wz)/r)
            w3 = ((wz*R)/r) - ((vx/1.732)/r) - ((vy/3)/r)
        
            w1 = int(127*w1)
            w2 = int(127*w2)
            w3 = int(127*w3)

            print w1,w2,w3,ds,k # can be directly used as rpms
            s= str(w1) + ':' + str(w2) + ':' + str(w3) +':'+str(ds) +':'+str(k) +':'
            sent = xbee.SendStr(s.encode())    
            clock.tick(20)
        except KeyboardInterrupt:
            break
    

    xbee.shutdown()
pygame.quit ()
