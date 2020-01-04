function gpsCallback(~,gpsMsg)
    global gndFusion
    global robotVel
    global Rvel
    lla = [gpsMsg.Latitude,gpsMsg.Longitude,gpsMsg.Altitude];
    % Measurement noises
    Rpos = 0;
    gpsVel = robotVel;
    fusegps(gndFusion, lla, Rpos, gpsVel, Rvel);
end