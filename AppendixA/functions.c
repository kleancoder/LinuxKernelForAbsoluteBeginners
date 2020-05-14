int system_status_check(int)
{
        return system_state == SYSTEM_RUNNING;
}
EXPORT_SYMBOL(system_status_check);
