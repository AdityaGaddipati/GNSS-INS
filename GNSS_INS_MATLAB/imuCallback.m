function imuCallback(~,imuMsg)
    global gndFusion
    gyroData = [imuMsg.AngularVelocity.X,imuMsg.AngularVelocity.Y,imuMsg.AngularVelocity.Z];
    accelData = [imuMsg.LinearAcceleration.X,imuMsg.LinearAcceleration.Y,-imuMsg.LinearAcceleration.Z];
    predict(gndFusion, accelData, gyroData);
end