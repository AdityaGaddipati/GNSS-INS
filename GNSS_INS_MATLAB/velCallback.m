function velCallback(~,velMsg)
    global robotVel
    global Rvel
    robotVel = [velMsg.Vector.X,velMsg.Vector.Y,velMsg.Vector.Z];
    % Measurement noise
    Rvel = 0.01;
    
end