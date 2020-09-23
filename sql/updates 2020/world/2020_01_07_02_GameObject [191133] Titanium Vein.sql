/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 7/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Titanium Vein';
SET @ENTRY 		:= '191133';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 4.1 Table  `gameobject_template */
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`,  `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '3', '6798', 'Titanium Vein', '', '', '', '0', '0', '0.5', '0', '0', '0', '0', '0', '0', '1785', '191133', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '80', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '65', '', '', '15595'); 


/* Step 4.1 Table  `gameobject */
DELETE FROM `gameobject` WHERE `id` = @ENTRY;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `phaseId`, `position_x`, `position_y`, `position_z`, `orientation`,`rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `protect_anti_doublet`) VALUES 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '6482.54', '2462.87', '468.117', '-1.91986', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4506', '1', '1', '0', '6481.97', '540.381', '438.703', '0.47124', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4282', '1', '1', '0', '6310', '3957.29', '109.057', '-0.76794', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4385', '1', '1', '0', '6302.94', '5136.3', '-81.6133', '-3.01941', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4385', '1', '1', '0', '6229.99', '5392.57', '-108.99', '-2.9845', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4385', '1', '1', '0', '6167.44', '5256.57', '-127.884', '0.89012', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4385', '1', '1', '0', '6107', '5455.44', '-97.4798', '2.93214', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4283', '1', '1', '0', '6084.56', '4079.1', '-46.7275', '-2.30383', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6077.97', '4860.72', '-94.5449', '-1.71042', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '5996.65', '2335.77', '518.032', '-0.5585', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '67', '4458', '1', '1', '0', '5990.99', '-621.435', '374.311', '-2.84488', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '67', '4458', '1', '1', '0', '5973.13', '-678.799', '384.303', '-1.01229', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5967.89', '1850.52', '630.557', '-0.5236', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '5961.09', '2412.07', '519.922', '2.51327', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5945.59', '4566.13', '-99.452', '1.69297', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5941.55', '1912.96', '567.54', '0.97738', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4615', '1', '1', '0', '5890.5', '1915.92', '-345.982', '-1.76278', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5889.07', '2160.36', '515.002', '-2.47837', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5877.63', '1942.75', '518.37', '-0.27925', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5843.15', '2256.14', '520.155', '-1.06465', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '5808.93', '2268.29', '523.321', '2.53072', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4615', '1', '1', '0', '5749.15', '2086.66', '-343.52', '-2.09439', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5740.39', '5960.09', '-36.3629', '0.5236', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4297', '1', '1', '0', '5721.06', '3655.52', '-25.2488', '0.27925', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5682.74', '3538.94', '-8.8133', '-2.35619', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4386', '1', '1', '0', '5671.01', '4389.62', '-137.554', '-1.46608', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4296', '1', '1', '0', '5668.26', '4118.6', '-90.1961', '2.37364', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4296', '1', '1', '0', '5652.2', '3981.09', '-83.0324', '-1.13446', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5553.28', '3666.73', '-28.5651', '-1.79769', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4293', '1', '1', '0', '5537.92', '4315.39', '-130.214', '-1.88495', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5482.81', '3505.6', '7.2101', '-2.68781', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4296', '1', '1', '0', '5479.19', '4193.7', '-97.0735', '0.80285', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4387', '1', '1', '0', '5456.09', '4679.77', '-173.517', '1.93731', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4285', '1', '1', '0', '5451.86', '5532.25', '-101.77', '0.22689', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4296', '1', '1', '0', '5449.87', '4089.35', '-91.0623', '1.88495', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4283', '1', '1', '0', '5434.91', '3826.25', '-65.5299', '1.09956', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4387', '1', '1', '0', '5418.62', '4371.29', '-137.676', '1.55334', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4290', '1', '1', '0', '5354.23', '4820.88', '-198.88', '1.6057', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5338.95', '4182.07', '-94.2039', '-2.93214', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5324.95', '5368.98', '-123.416', '-1.37881', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4292', '1', '1', '0', '5309.02', '4437.11', '-101.209', '2.9845', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5277.8', '3702.89', '12.7941', '1.76278', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4388', '1', '1', '0', '5226.19', '4826.15', '-132.704', '-2.77507', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5190.18', '6023.39', '-37.9963', '-0.76794', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4288', '1', '1', '0', '5159.02', '5454.54', '-88.2909', '3.03684', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4304', '1', '1', '0', '5128.38', '4215.86', '-83.4258', '1.6057', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5125.49', '6015.81', '-50.0045', '2.26892', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5105.15', '4639.76', '-135.884', '-1.02974', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4575', '1', '1', '0', '5097.4', '2734.82', '391.208', '-1.65806', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4288', '1', '1', '0', '5079.8', '5468.13', '-88.7503', '-0.27925', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5054.91', '4412.61', '-92.8146', '1.22173', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '5052.43', '5887.01', '-69.4098', '-1.69297', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4304', '1', '1', '0', '4993.83', '4180.02', '-79.1709', '0.01745', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4304', '1', '1', '0', '4927.28', '4328.63', '-72.9263', '0.59341', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4539', '1', '1', '0', '4910.04', '3429.39', '360.794', '2.3911', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4585', '1', '1', '0', '4859.01', '1843.17', '465.764', '2.79252', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4858.46', '3913.54', '380.702', '2.44346', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4837.23', '4160.79', '-3.6381', '-0.62832', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '4794.45', '5895.83', '-30.9455', '2.44346', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4738.39', '4691.45', '-56.7589', '0.50615', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4732.57', '5036.2', '-54.9473', '2.00713', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4576', '1', '1', '0', '4732.1', '2841.06', '360.432', '-0.95993', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4730.45', '2162.48', '373.443', '0.558504', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4722.86', '5246.86', '-42.0046', '1.18682', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4704.72', '5425.79', '-32.3253', '1.79769', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4577', '1', '1', '0', '4645.42', '2396.93', '337.234', '-0.942477', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4629.31', '2647.54', '373.596', '0.645772', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4586.99', '2144.87', '369.245', '3.05433', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4583.53', '1972.15', '412.869', '0.261798', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4562.71', '2070.25', '398.907', '-2.09439', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4576', '1', '1', '0', '4559.61', '2833.05', '359.045', '-2.74016', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4489.51', '3493.71', '365.425', '2.11185', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4584', '1', '1', '0', '4426.43', '1803.09', '369.678', '0.157079', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4581', '1', '1', '0', '4383.54', '1975.39', '390.425', '0.261798', '0', '0', '0', '1', '1800', '100', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4581', '1', '1', '0', '4383.28', '2008.55', '369.844', '2.18166', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4584', '1', '1', '0', '4366.34', '1737.62', '367.385', '-2.11185', '0', '0', '0', '1', '1800', '100', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4362.57', '1976.07', '360.856', '-2.58308', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4272.68', '2298.29', '345.954', '1.8675', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4584', '1', '1', '0', '4222.09', '1782.03', '350.871', '0.632817', '0', '0', '0.311156', '0.950359', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4584', '1', '1', '0', '4207.41', '1765.97', '356.537', '0.977383', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4049.9', '2580.41', '359.778', '-2.86233', '0', '0', '0', '1', '1800', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4012.23', '2581.06', '358.498', '-0.104719', '0', '0', '0', '1', '1800', '100', '1', '0', '0'), 
(NULL, @ENTRY, '571', '65', '65', '1', '1', '0', '3940.99', '3177.93', '402.245', '1.67551', '0', '0', '0', '1', '1800', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4477', '1', '1', '0', '8239.42', '2732.95', '647.622', '3.88232', '0', '0', '0.932197', '-0.361952', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4477', '1', '1', '0', '8170.95', '2669.15', '594.144', '4.49884', '0', '0', '0.778436', '-0.627724', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '210', '1', '1', '0', '8104.17', '2545.4', '524.975', '4.9465', '0', '0', '0.619685', '-0.784851', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '210', '1', '1', '0', '8010.1', '2449.39', '473.656', '4.04723', '0', '0', '0.899218', '-0.437501', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4540', '1', '1', '0', '7923', '2385.26', '407.431', '4.37316', '0', '0', '0.81632', '-0.5776', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4540', '1', '1', '0', '7922.72', '2276.9', '389.416', '5.12714', '0', '0', '0.546371', '-0.837543', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4510', '1', '1', '0', '7814.38', '2147.84', '364.625', '4.69123', '0', '0', '0.714547', '-0.699588', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4510', '1', '1', '0', '7674.82', '2138.18', '370.449', '3.68985', '0', '0', '0.962662', '-0.270708', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '210', '1', '1', '0', '7518.2', '2299.32', '384.884', '3.87834', '0', '0', '0.932914', '-0.3601', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4523', '1', '1', '0', '7380.59', '2390.04', '389.606', '2.68846', '0', '0', '0.974444', '0.224631', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4523', '1', '1', '0', '7188.84', '2434.38', '407.739', '3.36783', '0', '0', '0.993609', '-0.112879', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4515', '1', '1', '0', '7022.06', '2430.93', '412.777', '2.6217', '0', '0', '0.966404', '0.257027', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4515', '1', '1', '0', '6886.37', '2377.57', '427.764', '3.56811', '0', '0', '0.977347', '-0.211645', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4518', '1', '1', '0', '6735.75', '2337.04', '455.101', '3.95688', '0', '0', '0.918057', '-0.396448', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4518', '1', '1', '0', '6664.07', '2292.12', '651.117', '4.35348', '0', '0', '0.821965', '-0.569538', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4518', '1', '1', '0', '6664.89', '2195.94', '577.025', '3.83119', '0', '0', '0.941143', '-0.338008', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4597', '1', '1', '0', '6481.44', '2131.06', '501.405', '4.06288', '0', '0', '0.895766', '-0.444526', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4520', '1', '1', '0', '6378.51', '1961.21', '508.243', '0.575697', '0', '0', '0.28389', '0.958857', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4520', '1', '1', '0', '6378.51', '1961.21', '508.243', '0.575697', '0', '0', '0.28389', '0.958857', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5900.86', '3526.82', '32.8216', '6.15594', '0', '0', '0.0635776', '-0.997977', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4282', '1', '1', '0', '6074.5', '3658.88', '106.935', '0.540345', '0', '0', '0.266898', '0.963725', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4282', '1', '1', '0', '6175.66', '3792.66', '129.397', '0.622812', '0', '0', '0.306397', '0.951904', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4282', '1', '1', '0', '6319.99', '3983.55', '76.6067', '0.363631', '0', '0', '0.180815', '0.983517', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6407.72', '4090.98', '38.7668', '1.23542', '0', '0', '0.579171', '0.815206', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6466.53', '4232.31', '-15.4661', '1.23935', '0', '0', '0.580771', '0.814067', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4368', '1', '1', '0', '6570.49', '4370.5', '-26.6615', '0.548526', '0', '0', '0.270838', '0.962625', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6646.97', '4516.75', '5.4827', '1.22397', '0', '0', '0.574493', '0.81851', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6672.78', '4691.78', '6.18807', '1.46352', '0', '0', '0.668178', '0.744001', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4376', '1', '1', '0', '6629.27', '4870.98', '-31.6471', '1.12972', '0', '0', '0.535298', '0.844663', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6655', '5013.18', '-26.7879', '1.21219', '0', '0', '0.569662', '0.821879', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4308', '1', '1', '0', '6682.71', '5186.98', '-35.4216', '1.05904', '0', '0', '0.505117', '0.863051', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6543.77', '5292.11', '-34.0734', '2.35102', '0', '0', '0.922885', '0.385075', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6421.55', '5424.87', '-33.1081', '1.75019', '0', '0', '0.767603', '0.640926', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6328.1', '5522.85', '-13.3142', '2.08005', '0', '0', '0.862418', '0.506197', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6229.48', '5572.14', '-31.4321', '2.15859', '0', '0', '0.881626', '0.471949', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6137.52', '5671.82', '-35.8748', '1.31036', '0', '0', '0.609303', '0.792937', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6018.88', '5735.26', '-40.2238', '2.29604', '0', '0', '0.911953', '0.410295', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5894.05', '5848.54', '-30.2032', '2.34316', '0', '0', '0.921366', '0.388696', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5799.16', '5978.32', '-19.9421', '2.29604', '0', '0', '0.911953', '0.410296', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5689.6', '6025.12', '-33.8387', '2.54344', '0', '0', '0.955609', '0.294639', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5559.83', '5988.67', '-36.426', '3.3092', '0', '0', '0.996491', '-0.0837056', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '4784.5', '5876.17', '-19.1909', '3.48586', '0', '0', '0.985222', '-0.171285', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4766.69', '5656.51', '-25.0583', '3.49764', '0', '0', '0.984196', '-0.177085', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4483', '1', '1', '0', '4804.05', '5516.7', '-35.6561', '4.78176', '0', '0', '0.682159', '-0.731204', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4886.21', '5354.47', '-82.5478', '3.80787', '0', '0', '0.94502', '-0.327012', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4757.2', '5253.47', '-57.4024', '3.68221', '0', '0', '0.963689', '-0.267028', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4714.29', '4515.97', '-37.2351', '5.59028', '0', '0', '0.339564', '-0.940583', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4736.83', '4673.51', '-59.1125', '1.90283', '0', '0', '0.814239', '0.58053', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4722.93', '4882.16', '-49.9581', '1.74968', '0', '0', '0.767441', '0.641119', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4736.49', '4344.13', '-42.4727', '4.30223', '0', '0', '0.836288', '-0.548291', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4388', '1', '1', '0', '4812.54', '4192.98', '-6.01857', '4.64781', '0', '0', '0.729566', '-0.683911', '300', '0', '1', '0', '0'); 


/*## Step 2: GObject Loots ###########################################*/

/* Step x.x Table  `gameobject_loot_template */
DELETE FROM gameobject_loot_template WHERE  `entry` = @ENTRY;
INSERT INTO `gameobject_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES 
(@ENTRY, '36910', '100', '1', '0', '1', '3'), 
(@ENTRY, '37700', '10', '1', '1', '1', '4'), 
(@ENTRY, '37701', '10', '1', '1', '1', '4'), 
(@ENTRY, '37702', '10', '1', '1', '1', '4'), 
(@ENTRY, '37705', '10', '1', '1', '1', '4'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 36910;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('36910', '7', '7', '-1', 'Titanium Ore', '52908', '2', '262144', '8192', '0.9884', '1', '1', '7000', '1750', '0', '-1', '-1', '80', '0', '755', '450', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1024', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 37700;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('37700', '7', '10', '-1', 'Crystallized Air', '55240', '1', '1024', '8192', '0.9847', '1', '1', '2400', '600', '0', '-1', '-1', '75', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '49234', '0', '-1', '500', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '1224', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 37701;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('37701', '7', '10', '-1', 'Crystallized Earth', '60020', '1', '1024', '8192', '0.9884', '1', '1', '2400', '600', '0', '-1', '-1', '75', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '49248', '0', '-1', '500', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '1224', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 37702;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('37702', '7', '10', '-1', 'Crystallized Fire', '55241', '1', '1024', '8192', '0.992', '1', '1', '2400', '600', '0', '-1', '-1', '75', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '49244', '0', '-1', '500', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '1224', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 37705;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('37705', '7', '10', '-1', 'Crystallized Water', '60021', '1', '1024', '8192', '1.003', '1', '1', '2400', '600', '0', '-1', '-1', '75', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '49245', '0', '-1', '500', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '33992', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 2.6 GObject > Quest Items Data: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
36910  2  GREEN_UNCOMMON    0g 17s 50c  80  0  Titanium Ore
37700  1  WAIHT_COMMON      0g 6s 0c  75  0  Crystallized Air
37701  1  WAIHT_COMMON      0g 6s 0c  75  0  Crystallized Earth
37702  1  WAIHT_COMMON      0g 6s 0c  75  0  Crystallized Fire
37705  1  WAIHT_COMMON      0g 6s 0c  75  0  Crystallized Water
*/



/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `id`= @ENTRY;
/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `id`= @ENTRY;
/*## Step 3: GObjects Conditions #####################################*/

/*## Step 4: GObjects Needs to Work ##################################*/


