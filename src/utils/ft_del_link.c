 void    delete_process(t_process *pro)
 {
     t_process   *tmp;
     t_process   *tmp2;

     tmp = pro;
     ft_strdel(&pro->cmd);
     pro = pro->next
     while (pro && pro->next)
     {
         ft_strdel(&pro->cmd);
         tmp2 = pro;
         pro = pro->next;
         ft_memdel((void**)tmp2);
     }
     ft_memdel((void**)tmp);
 }


