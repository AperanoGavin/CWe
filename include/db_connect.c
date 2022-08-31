// #include <stdio.h>
// #include <stdlib.h>
#include <libpq-fe.h>

void do_exit(PGconn *conn) {
    
    PQfinish(conn);
    exit(1);
}

void insert_weather(char **json_string)
{
    char buffer[1024] = {};

    char query_string[] = { 
    "INSERT INTO Weather_Report(\
        Date_time, \
        Temp,\
        Feels_like, \
        Temp_max, \
        Temp_min, \
        Pressure, \
        Sea_lvl, \
        Grnd_lvl, \
        Humidity, \
        Temp_kf, \
        Main_cast, \
        Description, \
        Wind_speed, \
        Wind_deg, \
        Wind_gust, \
        Visibility, \
        Sunrise_time, \
        Sunset_time)\
    VALUES('%s', %s, %s, %s, %s, %s, %s, %s, %s, %s, '%s', '%s', %s, %s, %s, %s, %s, %s)" 
    };
    sprintf(buffer, query_string, json_string[15], json_string[0], json_string[1],\
    json_string[2], json_string[3], json_string[4], json_string[5],\
    json_string[6], json_string[7], json_string[8], json_string[9],\
    json_string[10], json_string[11], json_string[12], json_string[13],\
    json_string[14], json_string[17], json_string[18]);

    PGconn *conn = PQconnectdb("host=localhost user=ubuntu password=password dbname=ubuntu");
    PGresult* res;
    if(conn != NULL)
    {
        for(int i = 0; i < 1; i++)
        {
            res = PQexec(conn, buffer);
            if (PQresultStatus(res) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "%s\n", PQerrorMessage(conn));
                break;
            }
            PQclear(res);
            printf("Successfully sent !\n");
        }
        do_exit(conn);
    }
}

int go_weather(char **json_string) {
    
    PGconn *conn = PQconnectdb("host=localhost user=ubuntu password=password dbname=ubuntu");

    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
        do_exit(conn);
    }

    //int ver = PQserverVersion(conn);
    // printf("Server version: %d\n", ver);
    
    insert_weather(json_string);
    
    do_exit(conn);

    return('S');
}