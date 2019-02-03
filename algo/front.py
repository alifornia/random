def remove_dups(unique): 
    ret = [] 
    for strr in unique: 
        if strr.lower() not in ret: 
            ret.append(strr) 
    return ret 


print(remove_dups(["python", "java", "Python", "Java"]))