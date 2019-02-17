%Written by Jacob Peters
%Date: August 2015
%Description: This code establishes a serial connection with the arduino
%running readThermistorMUX.ino and saves data in a loop. The user will need
%to change FolderID and COM_port.

FolderID = '/Users/Jake/Desktop/';
cd(FolderID);
output_filename = [FolderID,datestr(now),'.csv'];
fid = fopen(output_filename,'a');
% I used a mac.. if you are using a PC, COM_port should be something like
% 'COM3'. 
COM_port = '/dev/cu.usbmodem1411';
s1 = serial(COM_port,'BaudRate',9600,'DataBits',8,...
    'StopBits',1,'Parity','none');
fopen(s1);
pause(5)

while 1
    
    read_1 = 0;
    % printing '1' to the serial connection requests data from the arduino
    fprintf(s1,'1');
    while read_1 == 0
        if s1.BytesAvailable > 0
            data_string = fscanf(s1);
            time = datestr(now);
            disp([time,',',data_string]);
            fprintf(fid,[time,',',data_string],'%s');
            read_1 = 1;
        end
    end
    
    thermistorVals = str2double(data_string);
    mean_internal_temp = mean([thermistorVals(1:2),thermistorVals(end)]);
    
    if mean_internal_temp <= 500
        fprintf(s1,'2'); % turn on heater
        disp([num2str(mean_internal_temp),'heater on'])
    elseif mean_internal_temp > 500
        fprintf(s1,'3'); % turn off heater
        disp([num2str(mean_internal_temp),'heater off'])
    end
            
    pause(5)
    
end

%%
fclose(s1);
fclose(fid);