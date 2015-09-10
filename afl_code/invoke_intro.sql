-- -------------------------------------------------------------------
-- © 2015 SAP AG or an SAP affiliate company. All rights reserved.
--
-- No part of this publication may be reproduced or transmitted in
-- any form or for any purpose without the express permission of
-- SAP AG. The information contained herein may be changed without
-- prior notice.
-- Some software products marketed by SAP AG and its distributors
-- contain proprietary software components of other software vendors.
-- National product specifications may vary.
--
-- These materials are provided by SAP AG and its affiliated
-- companies ("SAP Group") for informational purposes only, without
-- representation or warranty of any kind, and SAP Group shall not be
-- liable for errors or omissions with respect to the materials. The
-- only warranties for SAP Group products and services are those that
-- are set forth in the express warranty statements accompanying such
-- products and services, if any. Nothing herein should be construed
-- as constituting an additional warranty.
--
-- SAP and other SAP products and services mentioned herein as well
-- as their respective logos are trademarks or registered trademarks
-- of SAP AG in Germany and other countries.
-- -------------------------------------------------------------------

-- Execute as administrative user (e.g. SYSTEM).

-- Show available functions
select * from AFL_FUNCTIONS where AREA_NAME = 'INTRO_AREA';

-- Create test user
DROP USER TESTAFL CASCADE;
CREATE USER TESTAFL PASSWORD Pass1234;
ALTER USER TESTAFL DISABLE PASSWORD LIFETIME;

-- Grant execution privileges to test user
GRANT AFL__SYS_AFL_INTRO_AREA_EXECUTE TO TESTAFL;
GRANT AFLPM_CREATOR_ERASER_EXECUTE TO TESTAFL;

-- Switch to test user
CONNECT TESTAFL PASSWORD Pass1234;

-- DEMONSTRATE_DATATYPES
DROP TABLE T_I;
DROP TABLE T_O;
CREATE COLUMN TABLE T_I ("InputColumn" VARCHAR(100));
INSERT INTO T_I VALUES (7);
CREATE COLUMN TABLE T_O ("IntColumn" INT, "DoubleColumn" DOUBLE, "VarcharColumn" VARCHAR(100));
CALL _SYS_AFL.INTRO_AREA_DEMONSTRATE_DATATYPES_PROC(1, 9.5, 'Hello', T_I, ?, ?, ?, T_O) WITH OVERVIEW;
SELECT * FROM T_O;

-- DEMONSTRATE_FLEXIBLE_COLUMNS (make sure the wrapper generator procedure is created first)
DROP TYPE TYPE_IN;
CREATE TYPE TYPE_IN AS TABLE ("C_INT" INT, "C_VARCHAR" VARCHAR(90), "C_DOUBLE" double);
DROP TYPE TYPE_OUT;
CREATE TYPE TYPE_OUT AS TABLE ("ItemDataType" VARCHAR(987), "ItemId" INT, "ItemName" VARCHAR(100));
DROP TABLE SIGNATURE;
CREATE COLUMN TABLE SIGNATURE ( "POSITION" INT CS_INT, "SCHEMA_NAME" NVARCHAR(256) CS_STRING, "TYPE_NAME" NVARCHAR(256) CS_STRING, "PARAMETER_TYPE" VARCHAR(7) CS_STRING );
INSERT INTO SIGNATURE VALUES (1, 'TESTAFL', 'TYPE_IN', 'IN');
INSERT INTO SIGNATURE VALUES (2, 'TESTAFL', 'TYPE_OUT', 'OUT');
CALL SYS.AFLLANG_WRAPPER_PROCEDURE_DROP('TESTAFL', 'TEST_FLEXIBLE');
CALL SYS.AFLLANG_WRAPPER_PROCEDURE_CREATE('INTRO_AREA', 'DEMONSTRATE_FLEXIBLE_COLUMNS', 'TESTAFL', 'TEST_FLEXIBLE', SIGNATURE);
DROP TABLE T_I;
CREATE COLUMN TABLE T_I LIKE TYPE_IN;
INSERT INTO T_I VALUES (0, 'dummy', 5.555);
DROP TABLE T_O;
CREATE COLUMN TABLE T_O LIKE TYPE_OUT;
CALL TEST_FLEXIBLE(T_I, T_O) WITH OVERVIEW;
SELECT * FROM T_O;

-- DEMONSTRATE_PARALLELIZATION
DROP TABLE T_I;
CREATE COLUMN TABLE T_I("IntColumn" INT);
INSERT INTO T_I VALUES (1);
INSERT INTO T_I VALUES (2);
INSERT INTO T_I VALUES (3);
INSERT INTO T_I VALUES (4);
INSERT INTO T_I VALUES (5);
INSERT INTO T_I VALUES (6);
INSERT INTO T_I VALUES (7);
INSERT INTO T_I VALUES (8);
INSERT INTO T_I VALUES (9);
CALL _SYS_AFL.INTRO_AREA_DEMONSTRATE_PARALLELIZATION_PROC(T_I, ?);

-- APPEND_TO_STRING
DROP TABLE T_I;
DROP TABLE T_O;
CREATE COLUMN TABLE T_I ("StringColumn" VARCHAR(42));
CREATE COLUMN TABLE T_O ("StringColumn" VARCHAR(42));
INSERT INTO T_I VALUES('ONE');
INSERT INTO T_I VALUES('TWO');
INSERT INTO T_I VALUES('THREE');
CALL _SYS_AFL.INTRO_AREA_APPEND_TO_STRING_PROC(' for the show', T_I, T_O) WITH OVERVIEW;
SELECT * FROM T_O;

-- EVALUATE_EXPRESSION
DROP TABLE T_I;
DROP TABLE T_O;
CREATE COLUMN TABLE T_I ("X" DOUBLE);
CREATE COLUMN TABLE T_O ("X" DOUBLE, "Y" DOUBLE);
INSERT INTO T_I VALUES(0);
INSERT INTO T_I VALUES(1);
INSERT INTO T_I VALUES(2);
INSERT INTO T_I VALUES(3);
INSERT INTO T_I VALUES(4);
INSERT INTO T_I VALUES(5);

CALL _SYS_AFL.INTRO_AREA_EVALUATE_EXPRESSION_PROC('x^2', T_I, T_O) WITH OVERVIEW;
SELECT * FROM T_O;

TRUNCATE TABLE T_O;
CALL _SYS_AFL.INTRO_AREA_EVALUATE_EXPRESSION_PROC('2*(x + 1) + 3x^2', T_I, T_O) WITH OVERVIEW;
SELECT * FROM T_O;

TRUNCATE TABLE T_O;
CALL _SYS_AFL.INTRO_AREA_EVALUATE_EXPRESSION_PROC('1/x', T_I, T_O) WITH OVERVIEW;
SELECT * FROM T_O;

-- WAIT_FOR_CANCEL
-- Wait 5 seconds for user to cancel the call.
CALL _SYS_AFL.INTRO_AREA_WAIT_FOR_CANCEL_PROC(5, ?);
