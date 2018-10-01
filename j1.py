import pygame


pygame.init()

done = False

r = 50.760/1000 # metres
R = 150.000/1000 # metres
wz = 0.5 #rps

clock = pygame.time.Clock()

pygame.joystick.init()
    
while done==False:

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
        vy = joystick.get_axis(4)
        ds = joystick.get_axis(5)        

        vx = (vx/32000) * 0.2 ## value from -0.2 to 0.2
        vy = (vy/32000) * 0.2 ## value from -0.2 to 0.2    

        if ds < 0:
            ds = 0 ## value from 0 to 1
        ds = ds / 32000
        
        w1 = ((vx/1.732)/r) - ((vy/3)/r) + ((wz*R)/r)
        w2 = ((vy/1.5)/r) + ((R*wz)/r)
        w3 = ((wz*R)/r) - ((vx/1.732)/r) - ((vy/3)/r)
        
        buttons = joystick.get_numbuttons()

        A = joystick.get_button(0) ## 0 or 1 -> kick
        LB = joystick.get_button(4) ## 0 or 1 -> anti-clockwise rotation
        RB = joystick.get_button(5) ## 0 or 1 -> clockwise rotation
        
    clock.tick(20)
pygame.quit ()


















