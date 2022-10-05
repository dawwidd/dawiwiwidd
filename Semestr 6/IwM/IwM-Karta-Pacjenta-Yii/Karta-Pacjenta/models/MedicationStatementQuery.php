<?php

namespace app\models;

/**
 * This is the ActiveQuery class for [[MedicationStatement]].
 *
 * @see MedicationStatement
 */
class MedicationStatementQuery extends \yii\db\ActiveQuery
{
    /*public function active()
    {
        return $this->andWhere('[[status]]=1');
    }*/

    /**
     * {@inheritdoc}
     * @return MedicationStatement[]|array
     */
    public function all($db = null)
    {
        return parent::all($db);
    }

    /**
     * {@inheritdoc}
     * @return MedicationStatement|array|null
     */
    public function one($db = null)
    {
        return parent::one($db);
    }
}
