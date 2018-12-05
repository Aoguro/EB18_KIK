

void    ics_init(unsigned int addr, int level);
void    ics_watchpoint(void); 

/* interrupt */
void    int_sci_eri0();
void    int_sci_rxi0();
void    int_sci_txi0();
void    int_sci_tei0();

