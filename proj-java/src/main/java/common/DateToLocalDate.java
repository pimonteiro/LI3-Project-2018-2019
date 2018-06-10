package common;

import java.time.LocalDateTime;
import java.util.Date;

public abstract class DateToLocalDate {

    public LocalDateTime dateToLocalDateTime(Date d){
        return new java.sql.Timestamp(d.getTime()).toLocalDateTime();
    }
}
