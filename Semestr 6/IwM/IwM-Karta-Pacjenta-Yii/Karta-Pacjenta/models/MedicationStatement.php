<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "medicationStatement".
 *
 * @property int $id
 * @property string $concept
 * @property string $patientId
 */
class MedicationStatement extends \yii\db\ActiveRecord
{
    /**
     * {@inheritdoc}
     */
    public static function tableName()
    {
        return 'medicationStatement';
    }

    /**
     * {@inheritdoc}
     */
    public function rules()
    {
        return [
            [['id', 'concept', 'patientId'], 'required'],
            [['id'], 'integer'],
            [['concept', 'patientId'], 'string'],
            [['id'], 'unique'],
        ];
    }

    /**
     * {@inheritdoc}
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'concept' => 'Concept',
            'patientId' => 'Patient ID',
        ];
    }

    /**
     * {@inheritdoc}
     * @return MedicationStatementQuery the active query used by this AR class.
     */
    public static function find()
    {
        return new MedicationStatementQuery(get_called_class());
    }
}
