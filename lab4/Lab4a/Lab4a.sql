CREATE TABLE `Patient` (
`ID` text NOT NULL,
`ID_CARD` text NULL,
`NAME` text NULL,
`SEX` integer(255) NULL,
`DOB` text NULL,
`HEIGHT` real NULL,
`WEIGHRT` real(255,0) NULL,
`MOBILEPHONE` text NULL,
`AGE` integer NULL,
`CREATEDTIMESTAMP` text NULL,
PRIMARY KEY (`ID`) 
);

CREATE TABLE `History` (
`ID` text NOT NULL,
`USER_ID` text NULL,
`EVENT` text NULL,
`TIMESTAMP` text NULL,
PRIMARY KEY (`ID`) 
);

CREATE TABLE `User` (
`ID` text NOT NULL,
`FULLNAME` text NULL,
`USERNAME` text NULL,
`PASSWORD` text NULL,
PRIMARY KEY (`ID`) 
);

CREATE TABLE `Doctor` (
`ID` text NOT NULL,
`EMPLOYEENO` text NULL,
`NAME` text NULL,
`DEPARTMENT_ID` text NULL,
`HOSPITAL_ID` longtext NULL,
PRIMARY KEY (`ID`) 
);

CREATE TABLE `Department` (
`ID` text NOT NULL,
`NAME` text NULL,
PRIMARY KEY (`ID`) 
);


ALTER TABLE `History` ADD CONSTRAINT `fk_History_User_1` FOREIGN KEY (`USER_ID`) REFERENCES `User` (`ID`);
ALTER TABLE `Doctor` ADD CONSTRAINT `fk_Doctor_Department_1` FOREIGN KEY (`DEPARTMENT_ID`) REFERENCES `Department` (`ID`);

