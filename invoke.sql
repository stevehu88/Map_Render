DROP PROCEDURE "I075903"."RENDER_TILE";
CREATE PROCEDURE "I075903"."RENDER_TILE"(
    z INTEGER,
    x INTEGER,
    y INTEGER
)
LANGUAGE SQLSCRIPT
AS
BEGIN
    DECLARE base_z INTEGER := 14;
    DECLARE p INTEGER := POWER(2, ABS(:z - :base_z));
    DECLARE exist TINYINT :=0;
    DECLARE content CLOB;
    
    DECLARE lastest_time TIMESTAMP;
    SELECT MAX(TIMESTAMP) INTO lastest_time FROM  "I075903"."TPD_sapcd.itraffic.kpi.s.db::TPI.EDGE_SPEED";
    
    
    SELECT COUNT(1) INTO exist FROM "I075903"."TILE_IMAGE" WHERE Z = :z AND X = :x AND Y=:y AND TIMESTAMP=:lastest_time;
    
    IF :exist = 0 THEN

       IF :z >= 14 THEN
        segments =SELECT 
                        T5.FROM_LNG,
                        T5.FROM_LAT,
                        T5.TO_LNG,
                        T5.TO_LAT,
                        T4.SPEED_LEVEL,
                        T2.ONE_WAY,
                        T7.OFFSET AS OFFSET,
                        3 AS STROKE_WIDTH
        FROM
            "I075903"."TPD_sapcd.itraffic.kpi.s.db::TPI.EDGE_SPEED" T1,
            "I075903"."TPD_sapcd.itraffic.fdn.s.db::GIS.EDGES" T2,
            "I075903"."TPD_sapcd.itraffic.fdn.s.db::GIS.EDGE_SEGMENTS" T3,
            "I075903"."TPD_sapcd.itraffic.kpi.s.db::TPI.EDGE_SPEED_LEVEL" T4,
            "I075903"."MY_SEGMENTS" T5,
            "I075903"."MY_SEGMENGS_TILES_14" T6,
            "I075903"."TPD_sapcd.itraffic.kpi.s.db::MAP.ROAD_OFFSET" T7
            WHERE
                T1.EDGE_ID = T2.EDGE_ID
            AND T2.EDGE_ID = T3.EDGE_ID
            AND T2.WAY_CATEGORY = T4.WAY_CATEGORY
            AND T1.SPEED > IFNULL(T4.FROM_VALUE, -1)
            AND T1.SPEED < IFNULL(T4.TO_VALUE, 1000)
            AND T3.SEGMENT_ID = T5.SEGMENT_ID
            AND T5.SEGMENT_ID = T6.SEGMENT_ID
            AND T2.WAY_TYPE = T7.WAY_TYPE
            AND T1.TIMESTAMP = :lastest_time
            AND T7.ZOOM_LEVEL = :z
            AND T6.Z = :base_z
            AND T7.STYLE = 'dark'
                  AND T6.X = FLOOR(:x / :p)
                  AND T6.Y = FLOOR(:y / :p)

                ;
    ELSE
        segments =SELECT 
                        T5.FROM_LNG,
                        T5.FROM_LAT,
                        T5.TO_LNG,
                        T5.TO_LAT,
                        T4.SPEED_LEVEL,
                        T2.ONE_WAY,
                        T7.OFFSET AS OFFSET,
                        3 AS STROKE_WIDTH
        FROM
            "I075903"."TPD_sapcd.itraffic.kpi.s.db::TPI.EDGE_SPEED" T1,
            "I075903"."TPD_sapcd.itraffic.fdn.s.db::GIS.EDGES" T2,
            "I075903"."TPD_sapcd.itraffic.fdn.s.db::GIS.EDGE_SEGMENTS" T3,
            "I075903"."TPD_sapcd.itraffic.kpi.s.db::TPI.EDGE_SPEED_LEVEL" T4,
            "I075903"."MY_SEGMENTS" T5,
            "I075903"."MY_SEGMENGS_TILES_14" T6,
            "I075903"."TPD_sapcd.itraffic.kpi.s.db::MAP.ROAD_OFFSET" T7
            WHERE
                T1.EDGE_ID = T2.EDGE_ID
            AND T2.EDGE_ID = T3.EDGE_ID
            AND T2.WAY_CATEGORY = T4.WAY_CATEGORY
            AND T1.SPEED > IFNULL(T4.FROM_VALUE, -1)
            AND T1.SPEED < IFNULL(T4.TO_VALUE, 1000)
            AND T3.SEGMENT_ID = T5.SEGMENT_ID
            AND T5.SEGMENT_ID = T6.SEGMENT_ID
            AND T2.WAY_TYPE = T7.WAY_TYPE
            AND T1.TIMESTAMP = :lastest_time
            AND T7.ZOOM_LEVEL = :z
            AND T6.Z = :base_z
            AND T7.STYLE = 'dark'
	        AND T6.X BETWEEN :x * :p AND (:x + 1) * :p
	        AND T6.Y BETWEEN :y * :p AND (:y + 1) * :p
            ;
        
        END IF;
        CALL _SYS_AFL.INTRO_AREA_RENDER_TILE_PROC(:z, :x, :y, :segments, my_image) WITH OVERVIEW;
        SELECT CONTENT INTO content FROM :my_image;
        UPSERT "I075903"."TILE_IMAGE" VALUES(:z, :x, :y,:lastest_time, :content) WHERE X=:x AND Y=:y AND Z=:z;
    END IF;
    SELECT CONTENT FROM "I075903"."TILE_IMAGE" WHERE Z = :z AND X = :x AND Y=:y AND TIMESTAMP=:lastest_time;
END;

CALL RENDER_TILE(14,13595,6650);
