BEGIN{FS= " "}
{
student[$1,$2,$3] += $4;
}
END{for (k in student)
print k, student[k];
}
