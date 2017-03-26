#ifndef COMMON_H
#define COMMON_H

//对应tree 表中的属性
enum DBTreeKey {
    DB_TREE_NODEID = Qt::UserRole + 100,
    DB_TREE_PARENT_NODEID,
    DB_TREE_ERR_ID,
    DB_TREE_ERR_DESC,
    DB_TREE_RULE_ID,
    DB_TREE_ALARM_ID,
};


//对应rule 表中的属性
enum DBRuleKey {
    DB_RULE_RULEID = Qt::UserRole + 100,
    DB_RULE_ERR_DESC,
    DB_RULE_DETECT_TIP,
    DB_RULE_PARAMID,
    DB_RULE_JUDG,
    DB_RULE_SCHEMEID
};

//对应parameter 表中的属性
enum DBParamKey {
    DB_PARAM_PARAMID = Qt::UserRole + 100,
    DB_PARAM_PARAM_DESC,
    DB_PARAM_PARAM_TYPE,
    DB_PARAM_PARAM_UPPER_LIMIT,
    DB_PARAM_PARAM_LOWER_LIMIT
};

//对应scheme 表中的属性
enum DBSchemeKey {
    DB_SCHEME_ID = Qt::UserRole + 100,
    DB_SCHEME_DESC,
    DB_SCHEME_REPAIR,
};

#endif // COMMON_H
