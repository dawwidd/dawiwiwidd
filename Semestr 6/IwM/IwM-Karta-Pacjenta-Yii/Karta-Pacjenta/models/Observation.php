<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "observation".
 *
 * @property int $id
 * @property string $coding
 * @property float $value
 * @property string|null $unit
 * @property string|null $date
 * @property int|null $patientIdentifier
 */
class Observation extends \yii\db\ActiveRecord
{
    /**
     * {@inheritdoc}
     */
    public static function tableName()
    {
        return 'observation';
    }

    /**
     * {@inheritdoc}
     */
    public function rules()
    {
        return [
            [['id', 'coding', 'value'], 'required'],
            [['id', 'patientIdentifier'], 'integer'],
            [['coding', 'unit', 'date'], 'string'],
            [['value'], 'number'],
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
            'coding' => 'Coding',
            'value' => 'Value',
            'unit' => 'Unit',
            'date' => 'Date',
            'patientIdentifier' => 'Patient Identifier',
        ];
    }

    public function getDate()
    {
        return $this->date;
    }

    /**
     * {@inheritdoc}
     * @return ObservationQuery the active query used by this AR class.
     */
    public static function find()
    {
        return new ObservationQuery(get_called_class());
    }
}
