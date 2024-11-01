void __cdecl secret_backdoor( void )
{
    uint64_t local_0x88; // [rsp-136]

    fgets_2( &local_0x88, 128, stdin[0] );
    system_2( &local_0x88 );
}

void __cdecl handle_msg( void )
{
    uint64_t local_0xC8; // [rsp-200]
    uint64_t local_0x3C; // [rsp-60]
    uint64_t local_0x34; // [rsp-52]
    uint64_t local_0x2C; // [rsp-44]
    uint64_t local_0x24; // [rsp-36]
    uint64_t local_0x1C; // [rsp-28]
    uint32_t local_0x14; // [rsp-20]

    local_0x3C = 0;
    local_0x34 = 0;
    local_0x2C = 0;
    local_0x24 = 0;
    local_0x1C = 0;
    local_0x14 = 140;
    set_username( &local_0xC8 );
    set_msg( &local_0xC8 );
    puts_2( ">: Msg sent!" );
}

void __cdecl set_msg( int64_t p1 )
{
    uint64_t local_0x408; // [rsp-1032]
    int64_t v2; // rcx
    void * v1; // rdi

    v1 = &local_0x408;
    v2 = 128;
    while( v2 != 0 ) {
        *v1 = 0;
        (uint8_t *)v1 += 8;
        v2 += -1;
    }
    puts_2( ">: Msg @Unix-Dude" );
    printf_2( ">>: " );
    fgets_2( &local_0x408, 1024, stdin[0] );
    strncpy_2( p1, &local_0x408, (int32_t)*(p1 + 180) );
}

// VA=0x9cd
void __cdecl set_username( int64_t p1 )
{
    uint8_t local_0x98; // [rsp-152]
    uint32_t local_0xC; // [rsp-12]
    int64_t v2; // rcx
    void * v1; // rdi

    v1 = &local_0x98;
    v2 = 16;
    while( v2 != 0 ) {
        *v1 = 0;
        (uint8_t *)v1 += 8;
        v2 += -1;
    }
    puts_2( ">: Enter your username" );
    printf_2( ">>: " );
    fgets_2( &local_0x98, 128, stdin[0] );
    local_0xC = 0;
    while( (int32_t)local_0xC <= 40 && local_0x98[(int32_t)local_0xC] != 0 ) {
        *((int32_t)local_0xC + p1 + 140) = (uint32_t)local_0x98[(int32_t)local_0xC];
        local_0xC = (int32_t)local_0xC + 1;
    }
    printf_2( ">: Welcome, %s", p1 + 140 );
}

// VA=0xaa8
int32_t __cdecl main( void )
{
    puts_2( "--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------" );
    handle_msg();
    return 0;
}