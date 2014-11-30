
#if defined(_MSC_VER) &&_MSC_VER >=1800
static int v()
{
return _MSC_VER;
}
#else
#ifdef _MSC_VER
#error "This VisualStudio Is not Enable Windows Runtime "
#else
#error "Not A yet VisualC/C++"
#endif

#endif
