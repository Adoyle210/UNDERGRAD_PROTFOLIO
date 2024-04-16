
-- ACT 1

DROP TABLE IF EXISTS `Customers`;

-- Define table
CREATE TABLE `Customers` (
    `CustomerID` int NOT NULL AUTO_INCREMENT,
    `CustomerName` varchar(50),
    `AddressLine1` varchar(50),
    `AddressLine2` varchar(50),
    `City` varchar(50),
    `State` varchar(50),
    `PostalCode` varchar(50),
    `YTDPurchases` Decimal(19,2),
    PRIMARY KEY (`CustomerID`)
);

-- Show the tables available in the current database
SHOW TABLES;

-- Describe a specific table (i.e., DESCRIBE TableName)
DESCRIBE `Customers`;

-- Add data
INSERT INTO `Customers` (`CustomerName`, `AddressLine1`, `City`, `State`, `PostalCode`)
VALUES ('Bike World', '60025 Bollinger Canyon Road', 'San Ramon', 'California', '94583'),
('Metro Sports', '482505 Warm Springs Blvd.', 'Fremont', 'California', '94536'),
('Esport Express', '2222 A Real place Blvd.', 'Upland', 'Califonia', '91784');


-- More queries: 
-- Selects every record from customers
SELECT * FROM `Customers`;

-- Selects the ID and name where Postal Code is 94536.
SELECT `CustomerID`, `CustomerName` From `Customers` WHERE `PostalCode` = '94536';



-- ACT 3

DROP TABLE IF EXISTS `TermsCode`;

-- Define table
CREATE TABLE `TermsCode` (
    `TermsCodeID` varchar(50) NOT NULL,
    `Description` varchar(50),
    PRIMARY KEY (TermsCodeID)
);

-- Add data
INSERT INTO `TermsCode`  ( `TermsCodeID` , `Description` )
VALUES ('NET30', 'Payment due in 30 days.'),
('NET15' , 'Payment due in 15 days.'),
('210NET30', '2% discount in 10 days Net 30');


DROP TABLE IF EXISTS `Invoices`;

-- Define table
CREATE TABLE `Invoices` (
    `InvoiceID` int NOT NULL AUTO_INCREMENT,
    `CustomerID` int,
    `InvoiceDate` datetime,
    `TermsCodeID` varchar(50),
    `TotalDue` decimal(19,2),
    PRIMARY KEY (`InvoiceID`),
    FOREIGN KEY (`CustomerID`) REFERENCES `Customers` (`CustomerID`),
    FOREIGN KEY (`TermsCodeID`) REFERENCES `TermsCode` (`TermsCodeID`)      
);

-- Add Data
INSERT INTO `Invoices` (`CustomerID`, `InvoiceDate`, `TotalDue`, `TermsCodeID` )
VALUES (2, '2014-02-07', 2388.98, 'NET30'),
(1, '2014-02-02', 2443.35, '210NET30'),
(1, '2014-02-09', 8752.32, NULL);




-- ACT 2 

