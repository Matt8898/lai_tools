//! (string "56,78,91,67")
//! (string "54,21,45")
//! (string "98,67,21,28")
//! (string "26,84,01,37")

DefinitionBlock("out.aml", "DSDT", 1, "LAI", "LAI_TEST", 1)
{
    Scope(_SB)
    {
        Method(_INI)
        {
			Debug = ToDecimalString(Buffer(4){56, 78, 91, 67})
            Debug = ToDecimalString("54,21,45")

            Name(STR0, "")
            Name(BUF0, Buffer(4){98, 67, 21, 28})
            ToDecimalString(BUF0, STR0)
            Debug = STR0

            Name(STR1, "")
            Name(STR2, "26,84,01,37")
            ToDecimalString(STR2, STR1)
            Debug = STR1
        }
    }
}
